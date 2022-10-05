#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>

int tickets = 1000;
pthread_mutex_t lock;

void* RobTickets(void* arg)
{
    int number = (int)arg;
    while (1)
    {
       if (tickets > 0)
       {
           pthread_mutex_lock(&lock);
           if (tickets > 0)
           {
               usleep(1000);
               printf("[thread %d]抢票 : %d\n", number, tickets--);
               pthread_mutex_unlock(&lock);
           }
           else 
           {
               pthread_mutex_unlock(&lock);
               break;
           }
       }
       else 
       {
           break;
       }
    }
    printf("[thread %d] quit ...\n", number);
    pthread_exit((void*)0);
}

int main()
{
    pthread_t thds[5];
    int i = 0;
    pthread_mutex_init(&lock, NULL);

    for (i = 1; i < 6; i++)
    {
        pthread_create(&thds[i], NULL, RobTickets, (void*)i);
    }

    for (i = 1; i < 6; i++)
    {
        pthread_join(thds[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    return 0;
}
