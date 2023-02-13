#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig)
{
    switch(sig)
    {
        case 1:
            printf("我是1号信号\n");
            break;
        case 2:
            printf("我是2号信号\n");
            break;
        case 3:
            printf("我是3号信号\n");
            break;
        case 4:
            printf("我是4号信号\n");
            break;
        case 5:
            printf("我是5号信号\n");
            break;
        case 6:
            printf("我是6号信号\n");
            break;
        case 7:
            printf("我是7号信号\n");
            break;
    }
}

void func(int sig)
{
    printf("hello");
}

int main()
{
    int sig = 1;
     signal(sig, func);

     while (1)
     {
         printf("11");
         sleep(1);
     }

    //for (; sig <= 31; sig++)
    //{
    //    signal(sig, handler);
    //}
    
    return 0;
}
