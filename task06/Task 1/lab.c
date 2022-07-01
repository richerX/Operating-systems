#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int pfd;
    int fd[2];
    char array[100000];
    
    ssize_t size1, size2;
    size_t pipe_size = 0;
    
    pipe(fd);
    do {
    	size1 = write(fd[1], "a", 2);
        size2 = read(fd[0], array, 1);
        pipe_size += 2;
        printf("%ld\n", pipe_size);
    } while (size1 != size2);
    close(fd[0]);
    close(fd[1]);
    
    return 0;
    
    // 126'976 байт
}

