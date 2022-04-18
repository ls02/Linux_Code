#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

#define NUM 1024

int main(void)
{
    char str[NUM] = { 0 };
    char* myarg[30] = { 0 };
    while (1)
    {
        printf("myshell:>");
        fgets(str, NUM, stdin);
        str[strlen(str) - 1] = 0;
        myarg[0] = strtok(str, " ");

        int i = 1;
        while (myarg[i] = strtok(NULL, " "))
        {
            i++;
        }
        pid_t id = fork();

        if (id == 0)
        {
            execvp(myarg[0], myarg);
            exit(11);
        }

        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        if (ret > 0)
        {
            printf("exit code：%d\n", WEXITSTATUS(status));
        }

    }

    return 0;
}
