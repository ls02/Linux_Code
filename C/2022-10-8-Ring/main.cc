#include "Ring.hpp"
#include <stdlib.h>
#include <unistd.h>

void* consume(void* arg)
{
    RingQueue<int>* rq = (RingQueue<int>*)arg;
    
    while (true)
    {
        sleep(3);
        int x = 0;
        rq->Pop(x);

        std::cout << "consume done <<< " << x << std::endl;
    }
}

void* product(void* arg)
{
    RingQueue<int>* rq = (RingQueue<int>*)arg;
    
    while (true)
    {
        int x = rand() % 100 + 1;
        rq->Push(x);
        std::cout << "product done >>> " << x << std::endl;
    }
}

int main()
{
    srand((unsigned long)time(nullptr));
    RingQueue<int>* rq = new RingQueue<int>();
    pthread_t c, p;
    pthread_create(&c, nullptr, consume, rq);
    pthread_create(&c, nullptr, product, rq);

    pthread_join(c, nullptr);
    pthread_join(p, nullptr);

    return 0;
}
