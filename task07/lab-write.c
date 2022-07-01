#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>


int main() {
	key_t key = 5632;
	int semid, shmid;
	char *shmaddr;
	char string[]= "Hello, world!\0";
	struct sembuf sops;

	shmid = shmget(key, 256, IPC_CREAT | 0666);
	shmaddr = (char*)shmat(shmid, NULL, 0);

	semid = semget(key, 1, IPC_CREAT | 0666);
	semctl(semid, 0, IPC_SET, 0);
	sops.sem_num = 0;
	sops.sem_flg = 0;

	strcpy(shmaddr, string);
	sops.sem_op = 1; 
	semop(semid, &sops, 1);
		
	shmdt(shmaddr); 
	semctl(semid, 0, IPC_RMID, 0); 
	shmctl(shmid, IPC_RMID, NULL); 

	return 0;
}
