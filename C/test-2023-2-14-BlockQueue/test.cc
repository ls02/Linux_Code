#include "BlockQueue.hpp"
#include <string>
#include <unistd.h>
#include "Task.hpp"

//生产者不停生产数据
void* WorkProducer(void* args)
{
    ls::BlockQueue<Task>* bq = (ls::BlockQueue<Task>*)args;
    std::string ops = "+-*/%";

    while (true)
    {
        int x = rand() % 20 + 1;
        int y = rand() % 20 + 1;
        char op = ops[rand() % 5];
        Task t(x, y, op);

        std::cout << "生产者发布了一个任务：" << x << op << y << "=?" << std::endl;

        bq->Push(t);
        sleep(1);
    }
}

//消费者不停消费数据
void* WorkConsumer(void* args)
{
    ls::BlockQueue<Task>* bq = (ls::BlockQueue<Task>*)args;

    while (true)
    {
        Task t;
        bq->Pop(&t);
        t();
    }
}

int main()
{
    srand((size_t)time(nullptr));
    ls::BlockQueue<Task>* bq = new ls::BlockQueue<Task>();

    pthread_t producer;
    pthread_t consumer;
    pthread_t consumer1;
    pthread_t consumer2;
    pthread_t consumer3;

    pthread_create(&producer, nullptr, WorkProducer, (void*)bq);
    pthread_create(&consumer, nullptr, WorkConsumer, (void*)bq);
    pthread_create(&consumer1, nullptr, WorkConsumer, (void*)bq);
    pthread_create(&consumer2, nullptr, WorkConsumer, (void*)bq);
     pthread_create(&consumer3, nullptr, WorkConsumer, (void*)bq);

    pthread_join(producer, nullptr);
    pthread_join(consumer, nullptr);
    pthread_join(consumer1, nullptr);
    pthread_join(consumer2, nullptr);
    pthread_join(consumer3, nullptr);

    return 0;
}
