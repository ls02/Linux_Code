#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

#include "Log.hpp"

class Socket
{
public:
    Socket()
        : _sock_fd(-1)
    {
        memset(&_addr, sizeof(_addr), 0);
    }

    virtual bool CreateSocket(int domain, int type, int protocol);

    virtual ~Socket()
    {
        CloseSocket();
    }

    bool Bind(uint16_t port);

    virtual void CloseSocket();

    int GetFd();

protected:
    int _sock_fd;
    struct sockaddr_in _addr;
};

#endif