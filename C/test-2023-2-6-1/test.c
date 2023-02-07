#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <string.h>

int main()
{
    //close(1);
    int fd = open("abc.txt", O_RDONLY, 0644);

    char str[1024];
    int num = read(fd, str, sizeof(str));
    str[num - 1] = 0;

    printf("str: %s\n", str);

    //dup2(fd, 1);

    //printf("你好世界\n");
    //fflush(stdout);

    //const char* msg = "hello";
    //char str[1024];
    //
    //fgets(str, sizeof(str) - 1, stdin);

    //write(fd, str, strlen(str));

    close(fd);

    return 0;
}
