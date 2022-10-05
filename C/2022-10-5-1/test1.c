#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>

int tickets = 1000;
pthread_mutex_t lock;

void* RobTickets(void* arg)
{
    char* name = (char*)arg;
    while (1)
    {
       if (tickets > 0)
       {
           pthread_mutex_lock(&lock);
           if (tickets > 0)
           {
               usleep(1000);
               printf("[%s]抢票 : %d\n", name, tickets--);
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
    printf("[%s] quit ...\n", name);
    pthread_exit((void*)0);
}

int main()
{
    pthread_t t1, t2, t3, t4;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, RobTickets, "thread 1");
    pthread_create(&t2, NULL, RobTickets, "thread 2");
    pthread_create(&t3, NULL, RobTickets, "thread 3");
    pthread_create(&t4, NULL, RobTickets, "thread 4");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
