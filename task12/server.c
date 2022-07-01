#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 


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

    while (1)
    {
        msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, MESSAGE_TO_SERVER, 0);

        if (mybuf.stop_server) {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            break;
        }

        mybuf.type = mybuf.send_back_to;
        mybuf.number = mybuf.number * mybuf.number;
        msgsnd(msqid, (struct msgbuf *)&mybuf, maxlen, 0);
    }

    return 0;
}
