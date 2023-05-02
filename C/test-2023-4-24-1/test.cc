#include <string.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/select.h>
#include "Sock.hpp"

#define NUM (sizeof(fd_set) * 8)

int fd_array[NUM] = { 0 };

static void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << std::endl;
}

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        Usage(argv[0]);

        exit(1);
    }

    u_int16_t port = (uint16_t)atoi(argv[1]);
    int listen_sock = Sock::Socket();
    Sock::Bind(listen_sock, port);
    Sock::Listen(listen_sock);
    
    for (int i = 0; i < NUM; i++)
    {
        fd_array[i] = -1;
    }

    fd_set rfds;
    fd_array[0] = listen_sock;
    for ( ; ;  )
    {
        FD_ZERO(&rfds);
        int max_fd = fd_array[0];

        for (int i = 0; i < NUM; i++)
        {
            if (-1 == fd_array[i])
            {
                continue;
            }

            FD_SET(fd_array[i], &rfds);
            if (max_fd < fd_array[i])
            {
                max_fd = fd_array[i];
            }
        }

        struct timeval timeout = { 5, 0 };

        int n = select(max_fd + 1, &rfds, nullptr, nullptr, nullptr);
        switch (n)
        {
            case -1:
                std::cerr << "select error" << std::endl;
                break;
            case 0:
                std::cout << "select timeout" << std::endl;
                break;
            default:
                std::cout << "有fd对应的事件就绪啦" << std::endl;

                for (int i = 0; i < NUM; i++)
                {
                    if (-1 == fd_array[i])
                    {
                        continue;
                    }

                    if (FD_ISSET(fd_array[i], &rfds))
                    {
                        std::cout << "sock: " << fd_array[i] << " 上面有了读事件，可以读取了" << std::endl;
                        if (fd_array[i] == listen_sock)
                        {
                            std::cout << "listen_sock: " << listen_sock << "有了新的连接到来" << std::endl;
                            //accept
                            int sock = Sock::Accept(listen_sock);
                            if (sock >= 0)
                            {
                                std::cout << "listen_sock: " << listen_sock << "获取新的连接成功" << std::endl;
                                //获取成功
                                int pos = 1;
                                for(; pos < NUM; pos++)
                                {
                                    if (-1 == fd_array[pos])
                                    {
                                        break;
                                    }

                                }
                                // 1. 找到了一个位置没有被使用
                                if (pos < NUM)
                                {
                                    std::cout << "新连接: " << sock << "已经被添加到了数组[" << pos << "]的位置" << std::endl;
                                    fd_array[pos] = sock; 
                                }
                                else 
                                {
                                    std::cout << "服务器满载了" << std::endl;
                                    // 2. 找完了所有的 fd_array[] 都没有找到没有被使用的位置
                                    // 说明服务器已经满载没法处理新的请求了
                                    close(sock);
                                }
                            }
                        }
                        else 
                        {
                            std::cout << "sock: " <<  fd_array[i] << " 上面有普通读取" << std::endl;
                            //read, recv
                            char buff[1024] = { 0 };
                            ssize_t s = recv(fd_array[i], buff, sizeof(buff) - 1, 0);
                            if (0 < s)
                            {
                                buff[s] = 0;
                                std::cout << "client[" << fd_array[i] << "]# "<< buff << std::endl;
                            }
                            else if (0 == s)
                            {
                                std::cout << "sock: " << fd_array[i] << "关闭了,客户端退出了" << std::endl;
                                // 对端关闭了链接
                                close(fd_array[i]);
                                fd_array[i] = -1;
                                std::cout << "已经在数组下标fd_array[" << i << "]" << "中，去掉了sock: " << fd_array[i] << std::endl;
                            }
                            else 
                            {
                                // 读取失败
                                close(fd_array[i]);
                                fd_array[i] = -1;
                                std::cout << "已经在数组下标fd_array[" << i << "]" << "中，去掉了sock: " << fd_array[i] << std::endl;
                            }
                        }
                    }
                }

                break;
        }
    }

    return 0;
}
