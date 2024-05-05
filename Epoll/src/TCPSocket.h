#ifndef __TCP_SOCKET_H__
#define __TCP_SOCKET_H__

#include <iostream>
#include <cstring>
#include "Socket.h"
#include "nocopy.hpp"

class TCPSocket : public Socket
{
    static constexpr int backlog_num = 5;

public:
    TCPSocket() : Socket()
    {
    }

    // 创建套接字
    bool CreateSocket();

    // 监听套接字
    bool ListenSocket(int backlog = backlog_num);

    // 获取新链接
    int Accept(std::string *client_ip, uint16_t *client_port);

    bool Connect(const std::string &ip, const uint16_t &port);
};

#endif