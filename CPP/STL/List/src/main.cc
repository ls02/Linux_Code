#include <iostream>

#include "MyList.hpp"

int main(int argc, char *argv[]) {
    list<int> l1;

    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);

    list<int>::iterator it = l1.begin();
    while (it != l1.end()) {
        std::cout << *it << " ";
        ++it;
    }

    std::cout << std::endl;

    return 0;
}
