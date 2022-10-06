#include "BlockQueue.hpp"

void* Consumer(void* arg)
{
    auto bq = (BlockQueue<int>*)arg;
    while (true)
    {
        //sleep(1);
        int data = 0;
        bq->Pop(data); // 消费数据
        std::cout << "consumer: " << data << std::endl;
    }
}

void* Producter(void* arg)
{
    auto bq = (BlockQueue<int>*)arg;
    while (true)
    {
        sleep(1);
        int data = rand() % 100 + 1;
        bq->Push(data); //生产数据
        std::cout << "producter: " << data << std::endl;
    }
}

int main()
{
    srand((unsigned long)time(nullptr));
    BlockQueue<int>* bq = new BlockQueue<int>();

    pthread_t c, p;
    pthread_create(&c, nullptr, Consumer, bq);
    pthread_create(&p, nullptr, Producter, bq);

    pthread_join(c, nullptr);
    pthread_join(p, nullptr);

    return 0;
}
