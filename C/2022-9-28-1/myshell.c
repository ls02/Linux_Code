#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LEN 1024
#define NUM 32

int main()
{
    char cmd[LEN];
    char* myarg[NUM];

    while (1) 
    {
        printf("ls@centos # ");
        fgets(cmd, LEN, stdin);
        cmd[strlen(cmd) - 1] = '\0';
        myarg[0] = strtok(cmd," ");
        int i = 1;

        while (myarg[i] = strtok(NULL, " "))
        {
            i++;
        }

        pid_t id = fork();
        if (id == 0)
        {
            //child
            execvp(myarg[0], myarg);
            exit(11);
        }

        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        if (ret > 0)
        {
            printf("exit code %d\n", WEXITSTATUS(status));
        }
    }


    return 0;
}
