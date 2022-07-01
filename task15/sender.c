#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int signals[100];

int getPower(int number)
{
    int power = 1;
    if (number < 0)
    {
        number *= -1;
    }
    while (power <= number)
    {
        power *= 2;
    }
    power /= 2;
    return power;
}

int fillArray(int number, int power)
{
    if (number < 0)
    {
        signals[0] = 0;
        number *= -1;
    }
    else
    {
        signals[0] = 1;
    }

    int count = 1;
    while (power > 0)
    {
        if (number >= power)
        {
            number -= power;
            signals[count] = 1;
        }
        else
        {
            signals[count] = 0;
        }
        power /= 2;
        count++;
    }
    return count;
}

void send(int pid, int binary)
{
    int answer;
    if (binary == 0)
    {
        answer = kill(pid, SIGUSR1);
    }
    else if (binary == 1)
    {
        answer = kill(pid, SIGUSR2);
    }
    printf("Send %d to PID %d with answer = %d\n", binary, pid, answer);
    sleep(1);
}

void sendSignals(int pid, int count)
{
    send(pid, signals[0]);
    for (int i = count - 1; i > 0; --i)
    {
        send(pid, signals[i]);
    }
}

int main(void)
{
    int number;
    pid_t pid;

    printf("ID sender = %d\n", getpid());
    printf("ID receiver: ");
    scanf("%d", &pid);

    printf("Number to send: ");
    scanf("%d", &number);

    int power = getPower(number);
    int count = fillArray(number, power);
    sendSignals(pid, count);

    return 0;
}