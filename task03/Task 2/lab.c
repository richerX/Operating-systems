#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
	int pid = fork();
	
	if (pid == -1) {
		printf("Произошла ошибка");
	} else if (pid == 0) {
		printf("Это процесс ребенок\n");
	} else {
		printf("Это процесс родитель\n");
	}
	
	exit(pid);
}

