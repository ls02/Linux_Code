#pragma once 

#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

class UdpClient {
    private:
        int _sockfd;
        std::string _server_ip;
        int _server_port;
    public:
        UdpClient(std::string ip, int port)
            :_server_ip(ip), _server_port(port)
        {}

        bool InitUdpClient()
        {
            _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (_sockfd < 0)
            {
                std::cerr << "sockfd error!" << std::endl;

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
            
            for(; ;  )
            {
                std::cout << "Please Enter# ";
                std::cin >> msg;
                sendto(_sockfd, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));
                char buffer[128];
                struct sockaddr_in temp;
                socklen_t len = sizeof(temp);
                ssize_t size = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)& temp, &len);
                if (size > 0)
                {
                    buffer[size] = 0;
                    std::cout << buffer << std::endl;
                }
            }
        }

        ~UdpClient()
        {
            if (_sockfd >= 0) {
                close(_sockfd);
            }
        }
};
