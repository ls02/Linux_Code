#ifndef __EPOLL_H__
#define __EPOLL_H__
#include "nocopy.hpp"
#include <sys/epoll.h>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include "Log.hpp"

extern Log lg;

class Epoll : public NoCpy
{
    static constexpr int epoll_size = 64;

public:
    Epoll()
    {
        _epoll_fd = epoll_create1(EPOLL_CLOEXEC);
        if (_epoll_fd == -1)
        {
            lg(Error, "epoll_create error: %s", strerror(errno));
        }
        else
        {
            lg(Info, "epoll_create Success!, epoll_fd: %d", _epoll_fd);
        }
    }

    ~Epoll()
    {
        if (_epoll_fd >= 0)
        {
            close(_epoll_fd);
        }
    }

    int EpollWait(struct epoll_event revents[], int num);

    int EpollUpdate(int oper, int sock, uint32_t event);

private:
    int _epoll_fd;
    int _time_out{3000};
};

#endif