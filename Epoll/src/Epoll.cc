#include "Epoll.h"

int Epoll::EpollWait(struct epoll_event revents[], int num)
{
    return epoll_wait(_epoll_fd, revents, num, -1);
}

int Epoll::EpollUpdate(int oper, int sock, uint32_t event)
{
    int n = 0;
    if (oper == EPOLL_CTL_DEL)
    {
        n = epoll_ctl(_epoll_fd, oper, sock, nullptr);
        if (n)
        {
            lg(Error, "epoll_ctl delete error!");
        }
    }
    else
    {
        // EPOLL_CTL_MOD || EPOLL_CTL_ADD
        struct epoll_event ev;
        // 需要关系的事件和关心的文件描述符
        ev.events = event;
        ev.data.fd = sock;

        n = epoll_ctl(_epoll_fd, oper, sock, &ev);
        if (n)
        {
            lg(Error, "epoll_ctl error!");
        }
    }

    return n;
}