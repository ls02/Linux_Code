#pragma once 

#include "Reactor.hpp"
#include "Sock.hpp"
#include "Service.hpp"
#include "Util.hpp"

int Accepter(Event *evp)
{
    std::cout << "有新的链接到来了，就绪的socket是: " << evp->sock << std::endl;

    while (true)
    {
        int sock = Sock::Accept(evp->sock);
        if (0 > sock)
        {
            std::cout << "Accept Done!" << std::endl;
            break;
        }

        std::cout <<  "Accept success: " << sock << std::endl;
        SetNoBlock(sock);

        // 获取链接成功, io socke
        Event *other_ev = new Event();
        other_ev->sock = sock;
        other_ev->R = evp->R;
        // recver, sender, errorer, 就是我们代码中的较顶层，负责真正的读取
        other_ev->RegisterCallback(Recver, Sender, Errorer);

        evp->R->InsertEvent(other_ev, EPOLLIN | EPOLLET);
    }
}
