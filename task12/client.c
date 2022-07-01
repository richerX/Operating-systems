#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


struct mymsgbuf 
{
    long type;
    double number;
    long send_back_to;
    bool stop_server;
};


int main(void)
{
    char pathname[] = "server.c";
    key_t key = ftok(pathname, 0);
    int msqid = msgget(key, 0666 | IPC_CREAT);
    struct mymsgbuf mybuf;
    int maxlen = sizeof(mybuf);
    int MESSAGE_TO_SERVER = 1;
    long BACK_MESSAGE = getpid();

    printf("Input number: ");
    mybuf.type = MESSAGE_TO_SERVER;
    scanf("%lf", &mybuf.number);
    mybuf.send_back_to = BACK_MESSAGE;
    mybuf.stop_server = false;

    msgsnd(msqid, (struct msgbuf *)&mybuf, maxlen, 0);
    msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, BACK_MESSAGE, 0);
    printf("Squared = %lf\n", mybuf.number);

    return 0;
}
