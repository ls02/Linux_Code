#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUM 32

int main(void)
{
    

    while (1)
    {

    }

    return 0;
}

//int main(void)
//{
//    pid_t id = fork();
//    //char*  const  myavg[] = { "ls", "-a", "-l", NULL };
//    char*  const  myavg[] = { "top", NULL };
//
//    if (id == 0)
//    {
//        //execlp("ls", "ls", "-a", "-l", NULL);
//        
//        //execv("/bin/ls", myavg);
//        execv("/bin/top", myavg);
//    }
//
//    int status = 0;
//    pid_t ret = waitpid(id, &status, 0);
//
//    if (ret >= 0)
//    {
//        printf("waite child success!, %d\n", ret);
//
//        if (WIFEXITED(status))
//        {
//            printf("child get exit code:%d\n", WEXITSTATUS(status));
//        }
//        else
//        {
//            printf("chld not exit normal!\n");
//        }
//    }
//    
//
//    return 0;
//}
