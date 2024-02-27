#include <iostream>

#include "MyList.hpp"

void test1() {
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
}

void test2() {
    list<int> l1;

    /* l1.insert(l1.begin(), 1); */
    /* l1.insert(l1.begin(), 2); */
    /* l1.insert(l1.begin(), 3); */
    /* l1.insert(l1.begin(), 4); */

    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);

    printf("size: %ld\n", l1.size());

    l1.erase(l1.begin());
    l1.pop_back();
    printf("size: %ld\n", l1.size());

    list<int>::iterator it = l1.begin();
    while (it != l1.end()) {
        std::cout << *it << " ";
        ++it;
    }

    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    test2();

    return 0;
}
