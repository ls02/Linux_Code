#include "Stack.hpp"

void Test1(void)
{
    ls::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    std::cout << "栈的大小：" << s.size() << std::endl;
    std::cout << "栈顶数据：" << s.top() << std::endl;

    while (!s.empty())
    {
        std::cout << s.top() << std::endl;
        s.pop();
    }
}

int main(void)
{

    Test1();

    return 0;
}
