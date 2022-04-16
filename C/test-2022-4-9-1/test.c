#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
    pid_t arr[10];
    for (int i = 0; i < 10; i++)
    {
        pid_t id = fork();
        
        if (id == 0)
        {
            int count = 10;
            while (count > 0)
            {
                printf("I am child,pid:%d, ppid: %d\n", getpid(), getppid());
                sleep(1);
                count--;
            }

            exit(11);
        }
        
        arr[i] = id;
    }

    int count = 0;
    while (count < 10)
    {
        int status = 0;
        pid_t ret = waitpid(arr[count], &status, 0);
        
        if (ret >= 0)
        {
            printf("waite child success!,%d\n", ret);
            if (WIFEXITED(status))
            {
                printf("child get exit code:%d\n", WEXITSTATUS(status));
            }
            else
            {
                printf("child not exit normal!\n");
            }
            //printf("status: %d\n", status);
            //printf("child get singal:%d\n", status & 0x7F);
            //printf("child get exit code:%d\n", (status >> 8) & 0xFF);
        }

        count++;
    }
    
    return 0;
}
//int main(void)
//{
//    for (int i = 0; i < 10; i++)
//    {
//        pid_t id = fork();
//        if (!id)
//        {
//            printf("I am Child,pid:%d, ppid:%d\n", getpid(), getppid());
//            exit(11);
//        }
//        else
//        {
//            printf("I am parent, pid:%d,ppid:%d\n", getpid(), getppid());
//            int status = 0;
//            pid_t ret = wait(&status);
//            if (id >= 0)
//            {
//                printf("wait child success:%d\n", ret);
//                printf("child exit code:%d\n", (status >> 8) & 0xFF);
//                printf("child get signal:%d\n", status & 0x7F);
//    
//            }
//            sleep(2);
//         }
//    
//    }
//
//    return 0;
//}
//       
