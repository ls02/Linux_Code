#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    extern char** environ;

    char* arr[] = { "abc", "a", "b", "c"};
    char** str = arr;

    printf("%s\n", *arr);
    printf("%s\n", str[1]);

    return 0;
}

//int main()
//{
//    pid_t id = fork();
//
//    if (id > 0)
//    {
//        //父进程
//        printf("Parent: pid:%d\tppid:%d\n", getpid(), getppid());
//    }
//    else 
//    {
//        //子进程
//        printf("Child: pid:%d\tppid:%d\n", getpid(), getppid());
//        pid_t id = fork();
//
//        if (id > 0)
//        {
//            //父进程
//            printf("Parent: pid:%d\tppid:%d\n", getpid(), getppid());
//        }
//        else 
//        {
//            //子进程
//            printf("Child: pid:%d\tppid:%d\n", getpid(), getppid());
//        }
//    }
//
//    sleep(1);
//
//    return 0;
//}
