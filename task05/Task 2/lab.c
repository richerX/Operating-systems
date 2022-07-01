#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main() { 
	int fd1[2], result, fd2[2]; 
	char string1[] = "Hello, world! 1", string2[] = "Hello, world! 2"; 
	char new_string1[16], new_string2[16];
	size_t size; 
	
	pipe(fd1); 
	pipe(fd2); 
	result = fork();
	
	if (result < 0) { 
		printf("No child\n"); 
	} else if (result > 0) { 
		close(fd1[0]); 
		write(fd1[1], string1, 16); 
		close(fd1[1]); 
		printf("Parent process pause\n"); 
	} else { 
		close(fd2[0]); 
		close(fd1[1]); 
		read(fd1[0], new_string1, 16); 
		printf("%s\n", new_string1); 
		close(fd1[0]); 
		write(fd2[1], string2, 16); 
		close(fd2[1]); 
		printf("Child process ended\n"); 
	} 
	
	if (result > 0) { 
		close(fd2[1]); 
		read(fd2[0], new_string2, 16); 
		printf("%s\n", new_string2); 
		close(fd2[0]); 
		printf("Parent process ended\n"); 
	} 
	 
	return 0; 
}
