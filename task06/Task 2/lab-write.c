#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int     fd, result;
	size_t  size;
	char    resstring[14];
	char    name[] = "aaa.fifo";

	(void)umask(0);
	
	mknod(name, S_IFIFO | 0666, 0);
	printf("Waiting for read\n");
	fd = open(name, O_WRONLY);
	write(fd, "Hello, world!", 14);
	close(fd);
	
	printf("Finished writing\n");

	return 0;
}
