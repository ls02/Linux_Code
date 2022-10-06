#include "BlockQueue.hpp"
#include "Task.hpp"

void* Consumer(void* arg)
{
    auto bq = (BlockQueue<Task>*)arg;
    while (true)
    {
        sleep(1);
        Task t;
        int data = 0;
        bq->Pop(t); // 消费数据
        t.Run();
    }
}

void* Producter(void* arg)
{
    auto bq = (BlockQueue<Task>*)arg;
    const char* arr = "+-*/";
    while (true)
    {
        int x = rand() % 100 + 1;
        int y = rand() % 50;
        char op = arr[rand() % 4];
        Task t(x, y, op);

        bq->Push(t); //生产数据
        std::cout << "product task done" << std::endl;
    }
}

int main()
{
    srand((unsigned long)time(nullptr));
    BlockQueue<Task>* bq = new BlockQueue<Task>();

    pthread_t c, p;
    pthread_create(&c, nullptr, Consumer, bq);
    pthread_create(&p, nullptr, Producter, bq);

    pthread_join(c, nullptr);
    pthread_join(p, nullptr);

    return 0;
}
