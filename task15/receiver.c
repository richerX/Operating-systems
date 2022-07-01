#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int power = 1;
int number = 0;
int sign = 0;

void my_handler(int nsig)
{
    if (nsig == SIGUSR1)
    {
        if (sign == 0)
        {
            sign = -1;
        }
        else
        {
            power *= 2;
        }
        // printf("Received %d\n", 0);
    }
    else if (nsig == SIGUSR2)
    {
        if (sign == 0)
        {
            sign = 1;
        }
        else
        {
            number += power;
            power *= 2;
        }
        // printf("Received %d\n", 1);
    }
}

int main(void)
{
    (void)signal(SIGUSR1, my_handler);
    (void)signal(SIGUSR2, my_handler);

    pid_t sender_pid;
    printf("ID receiver = %d\n", getpid());
    printf("ID sender: ");
    scanf("%d", &sender_pid);

    while (kill(sender_pid, 0) == 0)
    {
    }
    printf("Received number = %d\n", number * sign);

    return 0;
}
