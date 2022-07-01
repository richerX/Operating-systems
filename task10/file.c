#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>


/*

ОПИСАНИЕ ПРОИСХОДЯЩЕГО В ПРОГРАММЕ

S = 1
for (n) {
    PARENT:
        D(S, 1);  <-- waits for child's A(S, 1)
        write();
        A(S, 2);
        D(S, 3);  <-- waits for child's A(S, 3)
        read()
    CHILD:
        D(S, 2);  <-- waits for parent's A(S, 2)
        read();
        write();
        A(S, 3);
        Z(S);
        A(S, 1);
}

*/


int main()
{
    int fd[2];
    size_t size;
    char resstring[15];
    pipe(fd);

    int semid = semget(ftok("file.c", 0), 1, 0666 | IPC_CREAT);
    struct sembuf clear, check, go1, wait1, go2, wait2, go3, wait3;

    clear.sem_num = 0;
    clear.sem_op  = -semctl(semid, 0, GETVAL);
    clear.sem_flg = 0;

    check.sem_num = 0;
    check.sem_op  = 0;
    check.sem_flg = 0;

    go1.sem_num = 0;
    go1.sem_op  = 1;
    go1.sem_flg = 0;

    go2.sem_num = 0;
    go2.sem_op  = 2;
    go2.sem_flg = 0;

    go3.sem_num = 0;
    go3.sem_op  = 3;
    go3.sem_flg = 0;


    wait1.sem_num = 0;
    wait1.sem_op  = -1;
    wait1.sem_flg = 0;

    wait2.sem_num = 0;
    wait2.sem_op  = -2;
    wait2.sem_flg = 0;

    wait3.sem_num = 0;
    wait3.sem_op  = -3;
    wait3.sem_flg = 0;

    // Зануляет семафор перед использовнием, возможно сохранения данных по semid от предыдущих запусков
    semop(semid, &clear, 1);
    semop(semid, &go1, 1);

    int n;
    printf("Введите число итераций: ");
    scanf("%d", &n);
    int result = fork();
    for (int i = 0; i < n; ++i) {
        if (result > 0) {
            semop(semid, &wait1, 1);
            printf("ITERTAION = #%d\n", i + 1);
            size = write(fd[1], "Parent message", 15);
            semop(semid, &go2, 1);
            semop(semid, &wait3, 1);
            size = read(fd[0], resstring, 15);
            printf("Parent got message = %s\n\n", resstring);
        } else if (result == 0) {
            semop(semid, &wait2, 1);
            size = read(fd[0], resstring, 15);
            printf("Child got message = %s\n", resstring);
            size = write(fd[1], "Child  message", 15);
            semop(semid, &go3, 1);
            semop(semid, &check, 1);
            semop(semid, &go1, 1);
        }
    }

    return 0;
}
