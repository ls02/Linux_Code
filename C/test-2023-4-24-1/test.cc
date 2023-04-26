#include <string.h>
#include <iostream>
#include <string>
#include <sys/select.h>
#include "Sock.hpp"

static void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << std::endl;
}

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        Usage(argv[0]);

        exit(1);
    }

    u_int16_t port = (uint16_t)atoi(argv[1]);
    int listen_sock = Sock::Socket();
    Sock::Bind(listen_sock, port);
    Sock::Listen(listen_sock);

    fd_set rfds;
    for ( ; ;  )
    {
        FD_ZERO(&rfds);
        FD_SET(listen_sock, &rfds);

        struct timeval timeout = { 5, 0 };

        int n = select(listen_sock + 1, &rfds, nullptr, nullptr, nullptr);
        switch (n)
        {
            case -1:
                std::cerr << "select error" << std::endl;
                break;
            case 0:
                std::cout << "select timeout" << std::endl;
                break;
            default:
                std::cout << "有fd对应的事件就绪啦" << std::endl;
                break;
        }
    }

    return 0;
}
