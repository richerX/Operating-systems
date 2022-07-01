#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[], char *envp[]) {
	int fd;
	size_t size;
	char *string = (char *) calloc(14, sizeof(char));
	
	fd = open("myfile.txt", O_RDONLY, 0666);
	size = read(fd, string, 14);
	printf("%s\n", string);
	close(fd);
	
	return 0;
}

