#include "Socket.h"

Log lg;

bool Socket::CreateSocket(int domain, int type, int protocol)
{
    int fd = socket(domain, type, protocol);
    if (fd < 0)
    {
        lg(Fatal, "CreateSocket Error, %s: %d", strerror(errno), errno);
        return false;
    }

    int opt = 1;
    setsockopt(_sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    _sock_fd = fd;

    return true;
}

void Socket::CloseSocket()
{
    if (_sock_fd != -1)
    {
        close(_sock_fd);
    }
}

bool Socket::Bind(uint16_t port)
{
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(port);

    if (bind(_sock_fd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
    {
        lg(Fatal, "Socket Bind ERROR, %s: %d", strerror(errno), errno);
        return false;
    }

    return true;
}

int Socket::GetFd()
{
    return _sock_fd;
}