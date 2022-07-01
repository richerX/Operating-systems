#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>


int main() {
	key_t key = 5632;
	int semid, shmid;
	char *shmaddr, st = 0;
	char string[14];
	struct sembuf sops;

	shmid = shmget(key, 256, IPC_CREAT | 0666);
	shmaddr = (char*)shmat(shmid, NULL, 0);

	semid = semget(key, 1, 0666);
	sops.sem_num = 0;
	sops.sem_flg = 0;

	sops.sem_op = -1;
	semop(semid, &sops, 1);
	strcpy(string, shmaddr);
	shmdt(shmaddr);
	
	printf("%s", string);

	return 0;
}
