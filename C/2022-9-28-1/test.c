#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t id = fork();

    if (id == 0)
    {
        //child
        int count = 0;
        while (count < 10)
        {
            printf("I am child, pid:%d, ppid:%d\n", getpid(), getppid());
            count++;
            sleep(1);
        }
        exit(11);
    }
    else 
    {
        //father
        printf("i am father, pid:%d, ppid:%d\n", getpid(), getppid());
        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        if (ret >= 0)
        {
            printf("wait child success!, %d\n\n", ret);
            if (WIFEXITED(status))
            {
                printf("child exit code: %d\n", WEXITSTATUS(status));
            }
            else
            {
                printf("child not exit normal!\n");
            }

            //printf("wait child success!, %d\n\n", ret);
            //printf("status: %d\n", status);
            //printf("childe exit code: %d\n", (status >> 8) & 0xFF);
            //printf("childe get signal: %d\n", status & 0x7f);
        }
        printf("Father run...");
        sleep(10);
    }
    

    return 0;
}
