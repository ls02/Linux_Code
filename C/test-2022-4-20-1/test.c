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

    char temp[32] = { 0 }; 
    read(fd, temp, strlen(str));
    printf("%s\n", temp);
    fflush(stdout);
    close(fd);
    
    return 0;
}
