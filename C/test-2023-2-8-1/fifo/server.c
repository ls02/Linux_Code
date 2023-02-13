#include "comm.h"

int main()
{
    umask(0);
    if (mkfifo(MY_FIFO, 0666) < 0)
    {
        perror("mkfifo\n");

        return 1;
    }

    int fd = open(MY_FIFO, O_RDONLY);
    if (fd < 0)
    {
        perror("open!\n");

        return 2;
    }

    //读取业务

    while (1)
    {
        char str[1024] = { 0 };
        int ret = read(fd, str, sizeof(str) - 1);
        if (ret > 0)
        {
            printf("读取成功：%s\n", str);

            if (strcmp(str, "ls") == 0)
            {
                if (fork() == 0)
                {
                    execlp("ls", "-l", "-a", NULL);

                    exit(0);
                }
            }
        }
        else if (0 == ret)
        {
            printf("读取到文件结尾!\n");
            break;
        }
        else 
        {
            perror("读取失败！\n");
            break;
        }
    }

    close(fd);

    return 0;
}
