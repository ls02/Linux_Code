#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int fd[2] = { 0 };
    if (pipe(fd) < 0)
    {
        perror("pipe!");
    }

    pid_t id = fork();
    if (id == 0)
    {
        //child
        
        close(fd[0]);
        const char* msg = "hello I am child";
        int count = 0;
        while (count < 10)
        {
            write(fd[1], msg, strlen(msg));
            sleep(1);
            count++;
        }

        close(fd[1]);
        exit(0);
    }

    close(fd[1]);
    char buff[64] = { 0 };

    while (1)
    {
       ssize_t s = read(fd[0], buff, sizeof(buff)); 
       if (s > 0)
       {
            buff[s] = 0;
           printf("I an father# %s %d\n", buff, s);
       }
       else if (s == 0)
       {
           printf("read end!\n");
           break;
       }
       else 
       {
           printf("error!\n");
           break;
       }
    }

    waitpid(id, NULL, 0); 
    close(fd[0]);


    return 0;
}
