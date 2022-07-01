#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[], char *envp[]) {
	printf("Кол-во аргументов командной строки = %d \n", argc);
	for (int i = 0; i < argc; ++i) {
		printf("Аргумент #%d = ", i+1);
		puts(argv[i]);
	}
	
	int index = 0;
	printf("\nАргументы окружающей среды\n");
	while (envp[index] != NULL) {
		printf("Аргумент #%d = ", index+1);
		puts(envp[index]);
		index++;
	}
	
	return 0;
}

