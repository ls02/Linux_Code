#include <functional>
#include <iostream>

using test = int;

test Add(test x, test y) { return x + y; }

void Print() {
    // std::cout << "All arguments have been printed." << std::endl;
    return;
}

template <typename T, typename... Args>
void Print(const T& fist_arg, const Args&... args) {
    std::cout << fist_arg << " " << std::endl;
    Print(args...);
}

void PrintInt(int a, int b, int c) {
    std::cout << "a: " << a << " b:" << b << " c:" << c << std::endl;
}

void Test1() {
    test x = 10;
    test y = 20;

    std::cout << "test1 :x + y = " << Add(x, y) << std::endl;

    auto bind_print = std::bind(PrintInt, std::placeholders::_3,
                                std::placeholders::_1, std::placeholders::_2);

    bind_print(1, 2, 3);

    Print("hello", "你好", "abc", 888, 3.2);
}

int main() {
    Test1();
    return 0;
}