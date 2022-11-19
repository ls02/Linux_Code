#pragma once
#ifndef __CLIENT_HPP__

#define __CLIENT_HPP__

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>

class Client 
{
    private:
        int _sockfd;
        int _server_port;
        std::string _server_ip;

    public:
        Client(int port, std::string ip)
            :_server_port(port)
             ,_server_ip(ip)
        {}

        bool InitClient()
        {
           _sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
           if (_sockfd < 0)
           {
               std::cout << "sockfd error" << std::endl;

               return false;
           }

           return true;
        }


        void Start()
        {
            struct sockaddr_in peer;
            memset(&peer, 0, sizeof(peer));
            peer.sin_family = AF_INET;
            peer.sin_port = htons(_server_port);
            peer.sin_addr.s_addr = inet_addr(_server_ip.c_str());

            std::string msg;
           
            for ( ; ; )
            {
                std::cout << "Please Enter# ";
                std::cin >> msg;

                sendto(_sockfd, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));
            }
        }

        ~Client()
        {
            if (_sockfd >= 0)
            {
                close(_sockfd);
            }
        }
};

#endif
