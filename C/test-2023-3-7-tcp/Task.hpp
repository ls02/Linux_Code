#ifndef __TASK_HPP__
#define __TASK_HPP__ 

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string>

namespace ns_task
{
    class Task 
    {
        private:
            int _sock;
        public:
            Task()
                :_sock(-1)
            {}

            Task(int sock)
                :_sock(sock)
            {}

            int Run()
            {
                while (true)
                {
                    char buffer[1024];
                    memset(buffer, 0, sizeof(buffer));
                    ssize_t s = read(_sock, buffer, sizeof(buffer) - 1);
                    if (s > 0)
                    {
                        buffer[s - 1] = 0;
                        std::cout << "client# " << buffer << std::endl;

                        std::string echo_string = ">>>server<<<, ";
                        echo_string += buffer;

                        write(_sock, echo_string.c_str(), echo_string.size());
                    }
                    else if (s == 0)
                    {
                        std::cout << "client quit ..." << std::endl;
                        break;
                    }
                    else 
                    {
                        break;
                    }
                }
                close(_sock);
            }

            ~Task()
            {}

    };
}

#endif
