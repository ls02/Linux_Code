#include "Queue.hpp"

void Test1(void)
{
    ls::queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);

    std::cout << "数据个数：" << q.size() << std::endl;
    std::cout << "队头：" << q.front() << std::endl;
    std::cout << "队尾：" << q.back() << std:: endl;

    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }

    std::cout << std::endl;
}

int main(void)
{
    Test1();

    return 0;
}
