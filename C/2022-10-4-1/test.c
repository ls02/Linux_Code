#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

//新线程
void* Routine(void* arg)
{
    char* msg = (char*)arg;
    int count = 0;
    while (count < 5)
    {
        printf("%s: pid:%d, ppid: %d, tid: %lu\n", msg, getpid(), getppid(), pthread_self());
        sleep(1);
        count++;
    }

    return (void*) 111;
}

//主线陈
int main()
{
    pthread_t tid[5];
    for (int i = 0; i < 5; i++)
    {
        //char buffer[64];
        char* buffer = (void*)malloc(64);
        sprintf(buffer, "thread %d", i);
        //sprintf(buffer, "thread 3");
        pthread_create(&tid[i], NULL, Routine, (void*)buffer);
        printf("%s tid is: %lu\n", buffer, tid[i]);
    }

   // while (1)
   // {
   //     printf("main thread: pid:%d, ppid: %d, tid: %lu\n", getpid(), getppid(), pthread_self());
   //     //printf("I am main thread!\n");
   //     sleep(2);
   // }
    
    printf("main thread: pid:%d, ppid: %d, tid: %lu\n", getpid(), getppid(), pthread_self());

    for (int i = 0; i < 5; i++)
    {
        void* ret = NULL;
        pthread_join(tid[i], &ret);
        printf("thread %d[%lu] ...quit!, code: %d\n", i, tid[i], (int)ret);
    }

    return 0;
}
