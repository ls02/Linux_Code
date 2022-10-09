#ifndef __TASK_H__

#define __TASK_H__

#include <iostream>
#include <pthread.h>

//typedef int (*handler_t)(int, int, char);

class Task{
    private:
        int x;
        int y;
        char op;
        //handler_t handler;
    public:
        Task()
        {}

        Task(int _x, int _y, char _op)
            :x(_x)
             ,y(_y)
             ,op(_op)
    {}

        void Run()
        {
            int z = 0;
            //任务处理
            //int ret = handler(x, y, op);
            switch(op)
            {
                case '+':
                    z = x + y;
                    break;
                case '-':
                    z = x - y;
                    break;
                case '*':
                    z = x * y;
                    break;
                case '/':
                    if (y == 0)
                    {
                        std::cerr << "div zero!" << std::endl;
                    }
                    if (y != 0)
                    {
                        z = x / y;
                    }
                    break;
                case '%':
                    if (y == 0)
                    {
                        std::cerr << "div zero!" << std::endl;
                    }
                    if (y != 0)
                    {
                        z = x % y;
                    }
                    break;
                default:
                    perror("operator error!\n");
                    break;
            }
            std::cout << "thread: [" << pthread_self() << " ]: "  << x << op << y << "=" << z << std::endl;
        }

        ~Task()
        {}

};

#endif
