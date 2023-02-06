#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM 1024
#define CMD_NUM 64

int main()
{
    char command[NUM] = { 0 };

    while(1)
    {
        printf("[ls@mydir]## ");
        fflush(stdout);
        fgets(command, NUM, stdin);
        command[strlen(command) - 1] = 0;
        const char* sep = " ";
        char* argv[CMD_NUM] = { NULL };
        int i = 1;
        argv[0] = strtok(command, sep);
        while (argv[i] = strtok(NULL, sep))
        {
            i++;
        }

        if (strcmp(argv[0], "cd") == 0)
        {
            if (argv[1] !=  NULL)
            {
                chdir(argv[1]);
            }
            continue;
        }

        if (fork() == 0)
        {
            execvp(argv[0], argv);
            exit(0);
        }

        int status = 0;
        waitpid(-1, &status, 0);
        printf("等待子进程成功！退出码：%d\n", (status >> 8) & 0xFF);

    }

    return 0;
}
