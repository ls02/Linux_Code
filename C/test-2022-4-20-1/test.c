#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(void)
{
    umask(0);
    int fd = open("bit.txt", O_CREAT | O_WRONLY, 0666);
    const char* str = "I like linux!\n";
    write(fd, str, strlen(str));
    close(fd);

    int fd1 = open("bit.txt", O_RDONLY);
    char ch;

    while (1)
    {
        size_t temp = read(fd1, &ch, 1);
        if (temp <= 0)
        {
            break;
        }

        write(1, &ch, 1);
        fflush(stdout);
    }
    close(fd1);
    
    return 0;
}
