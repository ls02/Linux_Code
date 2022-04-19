#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    umask(0);
    int fd = open("log.txt", O_WRONLY | O_CREAT, 0666);
    if (fd < 0)
    {
        printf("OpenFile error\n");
    }

    const char* str = "hello world\n";

    //write(fd, str, strlen(str));
    write(1, str, strlen(str));

    close(fd);

    printf("fd:%d\n", fd);
    //fputs("hello World\n", stdout);
    //FILE* fp = fopen("log.txt", "w");
    //fputs("hello\n", fp);
    //fclose(fp);

    return 0;
}
