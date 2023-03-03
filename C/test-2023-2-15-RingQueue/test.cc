#include "RingQueue.hpp"
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include "Task.hpp"

void* consumer(void* args)
{
     RingQueue<Task>* rq = (RingQueue<Task>*)args;
     while(true){
         Task t;
         rq->Pop(&t);
        //  std::cout << "消费数据是: " <<t.Show() << t() << "我是: " << pthread_self() << std::endl;
        t();  //比较耗时
         sleep(1);
     }
}

void* producter(void* args)
{
     RingQueue<Task>* rq = (RingQueue<Task>*)args;
     const std::string ops = "+-*/%";
     while(true){
         int x = rand()%20 + 1;
         int y = rand()%10 + 1;
         char op = ops[rand()%ops.size()];
         Task t(x, y, op);

         std::cout << "生产数据是:  " << t.Show() << "我是: " << pthread_self()<< std::endl;
         rq->Push(t);
        // sleep(1);
     }
}

int main()
{
    // 如果我们向改成多生产者，多消费者模型，该怎么改写
    srand((long long)time(nullptr));
    RingQueue<Task>* rq = new RingQueue<Task>();

    pthread_t c0,c1,c2,c3,p0,p1,p2;

    pthread_create(&c0, nullptr, consumer, (void*)rq);
    pthread_create(&c1, nullptr, consumer, (void*)rq);
    pthread_create(&c2, nullptr, consumer, (void*)rq);
    pthread_create(&c3, nullptr, consumer, (void*)rq);
    pthread_create(&p0, nullptr, producter, (void*)rq);
    pthread_create(&p1, nullptr, producter, (void*)rq);
    pthread_create(&p2, nullptr, producter, (void*)rq);

    pthread_join(c0, nullptr);
    pthread_join(c1, nullptr);
    pthread_join(c2, nullptr);
    pthread_join(c3, nullptr);
    pthread_join(p0, nullptr);
    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);

    return 0;
}
