#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM 5

pthread_mutex_t mutex;

int titke = 10000;

void* PthreadRun(void* argv)
{
    printf("%d\n", *(int*)argv);
    //while (1)
    //{
    //    pthread_mutex_lock(&mutex);
    //    if (titke > 0)
    //    {
    //        printf("抢票成功,我是线程[%d]: %d\n", *(int*)argv, titke); 
    //        usleep(1000);
    //        --titke;
    //    }
    //    else 
    //    {
    //        printf("抢票失败,我是线程[%d]\n", *(int*)argv);
    //        pthread_mutex_unlock(&mutex);

    //        break;
    //    }
    //    pthread_mutex_unlock(&mutex);
    //}

   return (void*)1;
}

int main()
{
    pthread_t tid[NUM];
    pthread_mutex_init(&mutex, NULL);
    
    for (int i = 0; i < NUM; i++)
    {
        pthread_create(&tid[i], NULL, PthreadRun, &i);
    }

    for (int i = 0; i < NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
