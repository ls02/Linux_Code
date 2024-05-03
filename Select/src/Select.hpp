#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include "Socket.hpp"

static constexpr int fd_num_max = sizeof(fd_set) * 8;
static constexpr uint16_t default_port = 8888;
static constexpr uint16_t default_fd = -1;

class SelectServer
{
public:
    SelectServer(uint16_t port = default_port) : _port(port)
    {
        // 初始化成-1, 因为fd不可能为负数
        for (int i = 0; i < fd_num_max; i++)
        {
            _fd_array[i] = default_fd;
        }
    }

    bool Init()
    {
        _listen_sock.CreateSocket();
        _listen_sock.BindSocket(_port);
        _listen_sock.ListenSocket();

        return true;
    }

    ~SelectServer()
    {
    }

    void Accept()
    {
        // 这个时候我们需要Accept这个新的fd，同时我们还需要把他设置进需要关系的数组事件里
        std::string ip;
        uint16_t port;

        // 返回一个建立好链接的文件描述符
        // 在这里Accept是不会阻塞的
        int sock_fd = _listen_sock.Accept(&ip, &port);
        if (sock_fd < 0)
        {
            // 说明获取出错了
            std::cerr << "Accept Error" << std::endl;
        }

        // 如果不小于0说明获取成功了
        // 设置进入需要关心的事件数组当中
        int pos = 1;
        for (int i = pos; i < fd_num_max; i++, pos++)
        {
            // 寻找没人占用的文件描述进行站位
            int fd = _fd_array[i];
            if (fd != default_fd)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        // 这里说明没人用
        if (pos == fd_num_max)
        {
            // 报错，超出能保存的最大直 1024
            lg(Warning, "server is full, close: %d now!", sock_fd);
            close(sock_fd);
        }
        else
        {
            _fd_array[pos] = sock_fd;
        }
    }

    void Recver(int sock_fd, int pos)
    {
        // 开始读取数据
        char buffer[1024]{0};

        ssize_t n = read(sock_fd, buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            // 说明读取成功了
            buffer[n] = 0;
            buffer[strcspn(buffer, "\r\n")] = 0;
            std::cout << "Client: " << buffer << std::endl;
            if (!strcasecmp(buffer, "quit"))
            {
                lg(Info, "Client quit, me too, close fd is : %d", sock_fd);
                close(sock_fd);
                // 因为关闭了，所以我们不需要继续关注这个文件描述付的事件了
                _fd_array[pos] = default_fd;
            }
        }
        else if (n == 0)
        {
            // 说明对端关闭了
            lg(Info, "Client quit, me too, close fd is : %d", sock_fd);
            close(sock_fd);
            // 因为关闭了，所以我们不需要继续关注这个文件描述付的事件了
            _fd_array[pos] = default_fd;
        }
        else
        {
            // 说明读取失败了
            lg(Warning, "recv errno: fd is : %d", sock_fd);
            close(sock_fd);
            // 因为关闭了，所以我们不需要继续关注这个文件描述付的事件了
            _fd_array[pos] = default_fd;
        }
    }

    void Dispatcher(fd_set *rfds)
    {
        // 我们不知道具体是哪个文件描述符事件就绪了，所以我们需要遍历整个数组来确定
        for (int i = 0; i < fd_num_max; i++)
        {
            int fd = _fd_array[i];
            if (fd == default_fd)
            {
                // 如果没被设置，说明一定没有
                continue;
            }

            // 走到这一定被设置了，但是不确定是不是在我们rfds中就绪的事件，我们需要确定一下
            if (FD_ISSET(fd, rfds))
            {
                // 如果是关心的事件 ready
                // 事件就绪分两种一种是读写事件，一种是建立链接事件，我们需要判断一下

                // 如果等于监听套接字,说明是建立链接事件
                if (fd == _listen_sock.GetFd())
                {
                    Accept();
                }
                else
                {
                    // 其他事件就绪
                    Recver(fd, i);
                }
            }
        }
    }

    void Start()
    {
        int listen_sock = _listen_sock.GetFd();
        _fd_array[0] = listen_sock;
        for (;;)
        {
            fd_set rfds;
            FD_ZERO(&rfds);

            int max_fd = _fd_array[0];
            // 把需要关心的文件描述付放进 fd_set 这个位图当中
            for (int i = 0; i < fd_num_max; i++)
            {
                if (_fd_array[i] == default_fd)
                {
                    continue;
                }
                FD_SET(_fd_array[i], &rfds);
                if (_fd_array[i] > max_fd)
                {
                    max_fd = _fd_array[i];
                    lg(Info, "max fd Update, max fd is: %d", max_fd);
                }
            }

            // 当设置好需要关心的文件描述符的时候，我们这个时候需要放进select当中，本次式例采用阻塞轮询
            // 如果传入这个参数说明是非阻塞
            struct timeval time_out = {0, 0};
            int n = select(max_fd + 1, &rfds, nullptr, nullptr, nullptr);
            switch (n)
            {
            case 0:
                // time out会返回0
                break;
            case -1:
                // 返回-1说明出错
                std::cerr << "select Error" << std::endl;
                break;

            default:
                // 说明有事件就绪了
                // 一个事件等于一个文件描述符
                Dispatcher(&rfds);
                break;
            }
        }
    }

private:
    Socket _listen_sock;
    uint16_t _port;
    int _fd_array[fd_num_max];
};

#endif