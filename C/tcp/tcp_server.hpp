#pragma once
#ifndef __TCP_SERVER_H__

#define __TCP_SERVER_H__

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#define BACKLOG 5

class TcpServer
{
    private:
        int _port;
        int _lsock;

    public:
        TcpServer(int port)
            :_port(port)
             ,_lsock(-1)
        {}

        bool InitTcpServer()
        {
            _lsock = socket(AF_INET, SOCK_STREAM, 0);
            if (_lsock < 0)
            {
                std::cerr << "lsock error" << std::endl;

                return false;
            }

            struct sockaddr_in local;
            memset(&local, 0, sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(_port);
            local.sin_addr.s_addr = INADDR_ANY;

            if (bind(_lsock, (struct sockaddr*)&local, sizeof(local)) < 0)
            {
                std::cout << "bind error" << std::endl;

                return false;
            }
    
            if (listen(_lsock, BACKLOG) < 0)
            {
                std::cerr << "listen error" << std::endl;

                return false;
            }

            return true;
        }

        void Loop()
        {
            for ( ; ;  )
            {
                struct sockaddr_in peer;
                socklen_t len = sizeof(peer);
                int sock = accept(_lsock, (struct sockaddr*)&peer, &len);
                if (sock < 0)
                {
                    std::cout << "accept error" << std::endl;

                    continue;
                }

                std::cout << "get a new link: " << sock << std::endl;
            }
        }

        ~TcpServer()
        {}
};

#endif
