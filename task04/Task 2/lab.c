#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
	int pid = fork();
	
	if (pid == -1) {
		printf("Произошла ошибка");
	} else if (pid == 0) {
		// Открывает мануал программиста Linux
		printf("Это процесс ребенок\n");
		execl("/usr/bin/man", "man", "execl", NULL);
	} else {
		wait(NULL);
		printf("Это процесс родитель\n");
	}
	
	exit(pid);
}

