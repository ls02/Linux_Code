#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t id = fork();
    
    if (!id)
    {
        int count = 10;

        while (count)
        {
            printf("I am Child  procsee...\n");
            printf("pid:%d\tppid:%d\n", getpid(), getppid());
            sleep(1);
            count--;
        }
    }
    else if (id > 0)
    {
        while (1)
        {
            printf("I am parent procsee...\n");
            printf("pid:%d\tppid:%d\n", getpid(), getppid());
            sleep(1);
        }
    }
    else
    {
        //...
    }

    return 0;
}
