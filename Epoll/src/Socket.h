#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

class Socket
{
public:
    Socket()
        : _sock_fd(-1)
    {
        memset(&_addr, sizeof(_addr), 0);
    }

    int CreateSocket(int domain, int type, int protocol);

    ~Socket()
    {
        CloseSocket();
    }

    void CloseSocket();

protected:
    int _sock_fd;
    struct sockaddr_in _addr;
};

#endif