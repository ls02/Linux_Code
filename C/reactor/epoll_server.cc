#include "Reactor.hpp"
#include "Sock.hpp"
#include "Accepter.hpp"
#include "Util.hpp"

void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << " proc" << std::endl;
}

int main(int argc, char *argv[])
{
        if (2 != argc)
        {
            Usage(argv[0]);

            exit(1);
        }

        // 1. 创建socket, 监听
        int listen_sock = Sock::Socket();
        SetNoBlock(listen_sock);
        Sock::Bind(listen_sock, (uint16_t)atoi(argv[1]));
        Sock::Listen(listen_sock);

        // 2. 创建 Reactor 对象
        Reactor *R = new Reactor();
        R->InitReactor();

        // 3. 给 Reactor 反应堆中加柴火
        // 3.1 有柴火
        Event *evp = new Event();
        evp->sock = listen_sock;
        evp->R = R;
        // Accepter: 链接管理器
        evp->RegisterCallback(Accepter, nullptr, nullptr);

        // 3.2 将准备好的柴火放入反应堆 Reactor 中
        R->InsertEvent(evp, EPOLLIN | EPOLLET);

        // 4. 开始事件派发! 
        int timeout = 1000;
        for ( ; ; )
        {
            R->DisPatcher(timeout);
        }

    return 0;
}
