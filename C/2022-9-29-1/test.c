#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    umask(0);

    int fd = open("log.txt", O_WRONLY | O_CREAT, 0666);

    printf("fd: %d\n", fd);


    return 0;
}
