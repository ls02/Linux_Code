#include "PriorityQueue.hpp"
#include <queue>

void Test1(void)
{
    std::priority_queue<int> Q;
    ls::PriorityQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    Q.push(1);
    Q.push(2);
    Q.push(3);
    Q.push(4);
    Q.push(5);

    std::cout << "优先级队列大小：" << q.size() << std::endl;
    std::cout << "优先级队列堆顶元素：" << q.top() << std:: endl;
    
    while (!q.empty())
    {
        std::cout << q.top() << " ";
        q.pop();
    }

    std::cout << std::endl;

    while (!Q.empty())
    {
        std::cout << Q.top() << " ";
        Q.pop();
    }

    std::cout << std::endl;
}


int main(void)
{
    Test1();

    return 0;
}
