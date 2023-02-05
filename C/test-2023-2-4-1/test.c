#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t id = fork();
    if (id == 0)
    {
        //child
        int n = 0;
        while (n < 10)
        {
            printf("I am child pid: %d  ppid: %d\n", getpid(), getppid());
            sleep(1);
            n++;
        }
        exit(11);
    }

    int n = 0;
    while (n < 5)
    {
        printf("I am father pid: %d  ppid: %d\n", getpid(), getppid()); 
        sleep(1);
        n++;
    }

    while (1)
    {
        int status = 0;
        int ret = waitpid(id, &status, WNOHANG);
        if (ret > 0)
        {
            printf("父进程等待成功！子进程ID：%d\n", ret);
            if (WIFEXITED(status))
            {
                printf("子进程正常结束，子进程退出码：%d\n", WEXITSTATUS(status));
            }
            else 
            {
                printf("子进程异常结束！");
            }
            break;
        }
        else if (ret == 0)
        {
            printf("等待子进程中....\n");
            sleep(1);
        }
        else 
        {
            printf("等待子进程失败!\n");
            break;
        }
    }

    //printf("===================begin wait==================\n");
    //sleep(15);

    //int status = 0;
    //int ret = waitpid(id, &status, 0);
    //printf("===================end wait====================\n");
    //if (ret >= 0)
    //{
    //    printf("父进程等待成功!子进程ID: %d\n", ret);
    //    if (WIFEXITED(status))
    //    {
    //        printf("子进程正常结束！子进程退出码：%d\n", WEXITSTATUS(status));
    //    }
    //    else 
    //    {
    //        printf("子进程异常结束\n");
    //    }
    //}
    //if (ret >= 0)
    //{
    //    printf("父进程等待成功!子进程ID: %d\n", ret);
    //    printf("子进程退出码：%d\t子进程退出信号：%d\n", (status >> 8) & 0xFF, status &0x7F);
    //}
    //else 
    //{
    //    printf("父进程等待失败！\n");
    //}

    //sleep(5);

    return 0;
}
