#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

int tickets = 1000;

void* TicketGreabbing(void* arg)
{
    const char* name = (char*)arg;
    while (1)
    {
        if (tickets > 0)
        {
            usleep(10000);
            printf("[%s] get a tickets : %d\n", name, tickets--);
        }
        else 
        {
            break;
        }
    }

    printf("%s quit!\n", name);
    pthread_exit((void*)0);
}

int main()
{
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, NULL, TicketGreabbing, "thread 1");
    pthread_create(&t2, NULL, TicketGreabbing, "thread 2");
    pthread_create(&t3, NULL, TicketGreabbing, "thread 3");
    pthread_create(&t4, NULL, TicketGreabbing, "thread 4");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);

    return 0;
}
