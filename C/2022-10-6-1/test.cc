#include <iostream>
#include <cstdio>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;

void* Run(void* arg)
{
    pthread_detach(pthread_self());
    std::cout << (char*)arg << " run.." << std::endl;
    while (true)
    {
        pthread_cond_wait(&cond, &lock);//阻塞在这里
        std::cout << "thread: " << pthread_self() << "活动..." << std::endl;
    }
}

int main()
{
    pthread_mutex_init(&lock, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_t t1, t2, t3;
    pthread_create(&t1, nullptr, Run, (void*)"thread 1");
    pthread_create(&t2, nullptr, Run, (void*)"thread 2");
    pthread_create(&t3, nullptr, Run, (void*)"thread 3");

    //ctrl
    while (true)
    {
        getchar();
        pthread_cond_signal(&cond);
    }

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
