#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "Log.hpp"
#include <cstring>

enum class TCPErr : int
{
    SOCKET_ERR = 2,
    BIND_ERR,
    LISTEN_ERR
};

static constexpr int backlog = 10;

class Socket
{
public:
    Socket()
        : _socket_fd(-1)
    {
    }

    ~Socket()
    {
        Close();
    }

    // 创建套接字
    void CreateSocket()
    {
        _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket_fd < 0)
        {
            lg(Fatal, "Create socket error, %s: %d", strerror(errno), errno);
            exit(static_cast<int>(TCPErr::SOCKET_ERR));
        }

        int opt = 1;
        setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    }

    // 绑定套接字
    void BindSocket(uint16_t port)
    {
        struct sockaddr_in server_addr;
        memset(&server_addr, sizeof(server_addr), 0);
        // 填充套接字
        // 服务端一般填充成0.0.0.0或者填充一个字段
        server_addr.sin_addr.s_addr = INADDR_ANY;
        // 填充端口
        // 主机序列转网络字节序
        server_addr.sin_port = htons(port);
        // 填充他的协议家族, AF_INET = IPV4
        server_addr.sin_family = AF_INET;

        if (bind(_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
            // 绑定失败报错并直接结束进程
            lg(Fatal, "Socket Bind error, %s: %d", strerror(errno), errno);
            exit(static_cast<int>(TCPErr::BIND_ERR));
        }
    }

    // 监听套接字
    void ListenSocket()
    {
        if (listen(_socket_fd, backlog) < 0)
        {
            lg(Fatal, "Listen Error, %s: %d", strerror(errno), errno);
            exit(static_cast<int>(TCPErr::LISTEN_ERR));
        }
    }

    // 获取新链接
    int Accept(std::string *client_ip, uint16_t *client_port)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);

        int new_fd = accept(_socket_fd, (struct sockaddr *)&peer, &len);
        if (new_fd < 0)
        {
            lg(Warning, "accept error, %s: %d", strerror(errno), errno);
            return -1;
        }

        char ip_str[64]{0};

        inet_ntop(AF_INET, &peer.sin_addr, ip_str, sizeof(ip_str));
        *client_ip = ip_str;
        *client_port = ntohs(peer.sin_port);

        return new_fd;
    }

    int GetFd()
    {
        return _socket_fd;
    }

    void Close()
    {
        close(_socket_fd);
    }

private:
    int _socket_fd;
};

#endif