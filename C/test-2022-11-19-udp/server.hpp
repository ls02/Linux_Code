#pragma once
#ifndef __SERVER_HPP__

#define __SERVER_HPP__

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT 8083

class Server 
{
    private:
        int _port;
        int _sockfd;
    public:
        Server(int port = DEFAULT, int sockfd = -1)
            :_port(port)
             ,_sockfd(sockfd)
        {}

        bool InitUdpServer()
        {
            // 获取网络文件符
            _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (_sockfd < 0)
            {
                std::cout << "sockfd error" << std::endl;

                return false;
            }

            std::cout << "sockfd create success, sockfd: " << _sockfd << std::endl;

            // 填充网络字段信息
           struct sockaddr_in local; 
           memset(&local, '\0', sizeof(local));
           local.sin_family = AF_INET;
           local.sin_port = htons(_port);
           local.sin_addr.s_addr = INADDR_ANY;

           if (bind(_sockfd, (struct sockaddr*)&local, sizeof(local)) < 0)
           {
               std::cout << "bind error" << std::endl;

               return false;
           }

           std::cout << "bind success" << std::endl;


           return true;
        }

#define SIZE 1024
        void Start()
        {
            char buffer[SIZE] =  { 0 };

            for ( ; ; )
            {
                struct sockaddr_in peer;
                socklen_t len = sizeof(peer);
                ssize_t size = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&peer, &len);
                if (size > 0)
                {
                    buffer[size] = 0;
                    int port = ntohs(peer.sin_port);
                    std::string ip = inet_ntoa(peer.sin_addr);
                    std::cout << ip << ":" << port << "#" << buffer << std::endl;
                }
            }
        }

        ~Server()
        {
            if (_sockfd >= 0)
            {
                close(_sockfd);
            }
        }
};

#endif
