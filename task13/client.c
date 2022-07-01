#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Результат
// Stopped process with i = 41.
// То есть глубина рекурсии на моей системе получилась 40.

int main(void)
{
    // int file;
    FILE *file;
    char current_filename[100] = "files/0", next_filename[100], link[100], buf[1024];
    fclose(fopen(current_filename, "w"));

    for (int i = 1; i < 1000; ++i) {
        sprintf(next_filename, "files/%d", i);
        sprintf(link, "%d", i - 1);
        symlink(link, next_filename);
        sprintf(current_filename, "files/%d", i);

        file = fopen(current_filename, "w");
        if (file == NULL) {
            printf("Stopped process with i = %d.\n", i);
            break;
        }
        fclose(file);
    }

    return 0;
}
