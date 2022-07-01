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
	
	fd = open(name, O_RDONLY);
	size = read(fd, resstring, 14);
	close(fd);
	
	printf("Finished reading\n");

	return 0;
}
