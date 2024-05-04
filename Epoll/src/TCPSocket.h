#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include <iostream>
#include <cstring>
#include "Socket.h"
#include "Log.hpp"

enum class TCPErr : int
{
    SOCKET_ERR = 2,
    BIND_ERR,
    LISTEN_ERR
};

class TCPServer : public Socket
{
public:
    TCPServer()
    {
    }

    void Init()
    {
        // 创建套接字
        if (CreateSocket(AF_INET, SOCK_STREAM, 0) < 0)
        {
            lg(Fatal, "Create Socket error, %s: %d", strerror(errno), errno);
            exit(static_cast<int>(TCPErr::SOCKET_ERR));
        }

        // 监听套接字
        if (ListenSocket() < 0)
        {
        }

        // 绑定套接字
        if (BindSocket() < 0)
        {
        }
    }

    int ListenSocket()
    {
        return listen(_sock_fd, )
    }

    int BindSocket()
    {
    }

private:
    int _listen_fd;
};

#endif