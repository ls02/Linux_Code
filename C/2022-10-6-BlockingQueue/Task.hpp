#ifndef __TASK_H__
#define __TASK_H__ 

#include <iostream>

class Task
{
    private:
        int x;
        int y;
        char op;
    public:
        Task(int _x, int _y, char _op)
            :x(_x)
            ,y(_y)
            ,op(_op)
        {}

        Task()
        {}

        void Run()
        {
            int result = 0;
            switch(op)
            {
                case '+':
                    result = x + y;
                    break;
                case '-':
                    result = x - y;
                    break;
                case '*':
                    result = x * y;
                    break;
                case '/':
                    if (0 == y)
                    {
                        std::cout << "Warning: div zero!" << std::endl;
                        result = -1;
                    }
                    else
                    {
                        result = x / y;
                    }

                    break;
                default:
                    break;
            }

            std::cout << x << op << y << "=" << result << std::endl;
        }

        ~Task()
        {

        }
};

#endif
