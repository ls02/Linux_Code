#ifndef __SOCK_HPP__
#define __SOCK_HPP__ 

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

class Sock
{
    public:
        static int Socket()
        {
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            if (0 > sock)
            {
                std::cerr << "socket error" << std::endl;

                exit(1);
            }

            int opt = 1;
            setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

            return sock;
        }

        static void Bind(int sock, uint16_t port)
        {
            struct sockaddr_in local;
            memset(&local, 0, sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = INADDR_ANY;

            if (0 > bind(sock, (struct sockaddr*) &local, sizeof(local)))
            {
                std::cerr << "bind error!" << std::endl;

                exit(2);
            }
        }

        static void Listen(int sock)
        {
            if (0 > listen(sock, 5))
            {
                std::cerr << "listen error!" << std::endl;

                exit(3);
            }
        }

        static int Accept(int sock)
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int fd = accept(sock, (struct sockaddr*)&peer, &len);
            if (0 <= fd)
            {
                return fd;
            }
            return -1;
        }

        static void Connect(int sock, std::string ip, uint16_t port)
        {
            struct sockaddr_in server;
            memset(&server, 0, sizeof(server));

            server.sin_family = AF_INET;
            server.sin_port = htons(port);
            server.sin_addr.s_addr = inet_addr(ip.c_str());

            if (0 == connect(sock, (struct sockaddr*)&server, sizeof(server)))
            {
                std::cout << "Connect Success!" << std::endl;
            }
            else 
            {
                std::cout << "Connect Failed!" << std::endl;

                exit(5);
            }
        }
};

#endif
