#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    umask(0);
    //close(1);

    //int fd = open("log.txt", O_WRONLY | O_CREAT, 0666);
    //int fd = open("log.txt", O_WRONLY | O_APPEND, 0666);
    int fd = open("log.txt", O_RDONLY, 0666);
    if (fd == -1)
    {
        perror("open failed!\n");
        exit(1);
    }
    else 
    {
        printf("open success!\n");
    }

    //printf("fd: %d\n", fd);
   // char* ch = "hello\n";
   // int count = 0;
   // //dup2(fd, 1);
   // 
   // 
   // while (count < 3)
   // {
   //     //write(fd, ch, strlen(ch));
   //     write(1, ch, strlen(ch));
   //     count++;
   // }
   
    char ch[3] = { 0 };
    while (read(fd, ch, sizeof(ch)))
    {
        printf("%s", ch);
    }

    close(fd);

    return 0;
}
