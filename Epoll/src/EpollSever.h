#ifndef __EPOLL_SERVER_H__
#define __EPOLL__SERVER_H__
#include <iostream>
#include "nocopy.hpp"
#include "Epoll.h"
#include <memory>
#include "TCPSocket.h"

extern uint32_t EVENT_IN;
extern uint32_t EVENT_OUT;

class EpollServer : public NoCpy
{
    static constexpr int defalut_num = 64;

public:
    EpollServer(uint16_t port)
        : _port(port),
          _tcp_ptr(new TCPSocket),
          _epoll_ptr(new Epoll)
    {
    }

    void Init();

    void Start();

    void Dispatcher(struct epoll_event revs[], int num);

    void Accepter();

    void Recver(int fd);

private:
    std::shared_ptr<TCPSocket> _tcp_ptr;
    std::shared_ptr<Epoll> _epoll_ptr;
    uint16_t _port;
};

#endif