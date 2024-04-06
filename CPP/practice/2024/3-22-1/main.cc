#include <unistd.h>

#include <iostream>
#include <thread>

void ThreadRun() {
    while (1) {
        std::cout << "Thread Pid: " << getpid() << ":" << gettid() << std::endl;
        sleep(1);
    }
}

int main(int argc, char const *argv[]) {
    std::thread t1(ThreadRun);

    while (1) {
        std::cout << "Thread Pid: " << getpid() << std::endl;
        sleep(1);
    }

    t1.join();

    return 0;
}

// void *ThreadRun(void *args) {
//     int a = *(int *)args;
//     int count = 10;
//     while (1) {
//         std::cout << "Thread Pid: " << getpid() << ":" << a << ":" <<
//         gettid()
//                   << std::endl;
//         sleep(1);
//
//         count--;
//         if (!count) {
//             break;
//         }
//     }
//
//     return (void *)3;
// }
//
// int main() {
//     std::cout << "hello" << std::endl;
//     pthread_t t_id;
//     int a = 20;
//     int count = 5;
//
//     pthread_create(&t_id, nullptr, ThreadRun, (void *)&a);
//
//     while (1) {
//         std::cout << "main Pid: " << getpid() << std::endl;
//         sleep(1);
//         count--;
//         if (!count) {
//             break;
//         }
//     }
//
//     void *ret_val;
//     int tmp = pthread_join(t_id, &ret_val);
//
//     std::cout << "main tmp: " << tmp << "\t ret_val: " << (long long
//     int)ret_val
//               << std::endl;
//
//     return 0;
// }