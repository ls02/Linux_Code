#pragma once 

#include <iostream>
#include <string>
#include <stdlib.h>
#include <unordered_map>
#include <sys/epoll.h>
#include <unistd.h>

#define SIZE 128 
#define NUM 64

class Event;
class Reactor;

typedef int (*callback_t)(Event *ev);

// 需要让 epoll 管理的基本节点
class Event
{
    public:
        int sock; // 对应的文件描述符

        std::string inbuffer; // 对应的 sock 对应的输入缓冲区
        std::string outbuffer; // 对应的 sock 对应的输出缓冲区

        // sock 设置回调
        callback_t recver;
        callback_t sender;
        callback_t errorer;

        // 设置 Event 回指 Reactor 的指针
        Reactor *R;

    public:
        Event()
        {
            sock = -1;
            recver = nullptr;
            sender = nullptr;
            errorer = nullptr;  
            R = nullptr;
        }

        void RegisterCallback(callback_t _recver, callback_t _sender, callback_t _errorer)
        {

            recver = _recver;
            sender = _sender;
            errorer = _errorer;  
        }

        ~Event()
        {

        }
};

class Reactor 
{
    private:
        int epfd;
        std::unordered_map<int, Event*> events; // 我的 Reactor 类管理的所有的Event的集合

    public:
        Reactor() : epfd(-1)
        {
        }

        void InitReactor()
        {
            epfd = epoll_create(SIZE);
            if (0 > epfd)
            {
                std::cerr << "epoll_create error" << std::endl;
                exit(2);
            }

            std::cout << "InitReactor success" << std::endl;
        }

        bool InsertEvent(Event *evp, uint32_t evs)
        {
            // 1. 将 ev 中的 sock 插入到 epoll 中
            struct epoll_event ev;
            ev.events = evs;
            ev.data.fd = evp->sock;

            if (0 > epoll_ctl(epfd, EPOLL_CTL_ADD, evp->sock, &ev))
            {
                std::cerr << "epoll_ctl add event failed" << std::endl;
                return false;
            }
            // 2. 将 ev 本身插入到 unordered_map 中
            
            events.insert({evp->sock, evp});

            return true;
        }

        void DeleteEvent(Event *evp)
        {
            int sock = evp->sock;
            auto iter = events.find(sock);
            if (iter != events.end())
            {
                // 1. 将 sock 中的 sock 从 epoll 中删除它
                epoll_ctl(epfd, EPOLL_CTL_DEL, sock, nullptr);
                // 2. 将特定的 ev 从 unordered_map 中移除
                events.erase(iter);

                // 3. close
                close(sock);

                // 4. 删除 event 节点
                delete evp;
            }
        }

        bool EnaleRW(int sock, bool enable_read, bool enable_write)
        {
            struct epoll_event ev;
            ev.events = EPOLLET | (enable_read ? EPOLLIN : 0) | (enable_write ? EPOLLOUT: 0);
            ev.data.fd = sock;

            if (0 > epoll_ctl(epfd, EPOLL_CTL_MOD, sock, &ev))
            {
                std::cerr << "epoll_ctl mod event failed" << std::endl;

                return false;
            }

            return true;
        }

        bool IsSockOk(int sock)
        {
            auto iter = events.find(sock);

            return iter == events.end();
        }
        
        // 就绪事件的派发器逻辑
        void DisPatcher(int timeout)
        {
            struct epoll_event revs[NUM];
            int n = epoll_wait(epfd, revs, NUM, timeout);
            for (int i = 0; i < n; i++)
            {
                int sock = revs[i].data.fd;
                uint32_t revents = revs[i].events;

                // 代表差错处理， 为了将所有的错误问题全部转换成为让 IO 函数去解决
                if (revents & EPOLLERR)
                {
                    revents |= (EPOLLIN | EPOLLOUT);
                }

                if (revents & EPOLLHUP)
                {
                    revents |= (EPOLLIN | EPOLLOUT);
                }

                // 读数据就绪
                if (revents & EPOLLIN)
                {
                    // 直接调用回调方法，执行对应的读取
                    if ((IsSockOk(sock)) && events[sock]->recver)
                    {
                        events[sock]->recver(events[sock]);
                    }
                }

                if (revents & EPOLLOUT)
                {
                    if ((IsSockOk(sock)) && events[sock]->sender)
                    {
                        events[sock]->sender(events[sock]);
                    }
                }
            }
        }

        ~Reactor()
        {

        }

};
