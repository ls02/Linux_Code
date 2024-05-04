#include "Socket.h"

int Socket::CreateSocket(int domain, int type, int protocol)
{
    int fd = socket(domain, type, protocol);
    _sock_fd = fd;
    return fd;
}

void Socket::CloseSocket()
{
    if (_sock_fd != -1)
    {
        close(_sock_fd);
    }
}