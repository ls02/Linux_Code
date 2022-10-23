#pragma oce 

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define DEFAULT 8083

class UdpServer{
    private:
        int _port;
        int _sockfd;
//        std::string _ip;

    public:
    UdpServer(int port = DEFAULT, int sockfd = -1): _port(port), _sockfd(sockfd) 
    {}

    bool InitUdpServer1()
    {
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            std::cerr << "socket error" << std::endl;

            return false;
        }

        std::cout << "socket create success, sockfd: " << _sockfd << std::endl;

        struct sockaddr_in local;
        memset(&local, '\0', sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        //local.sin_addr.s_addr = inet_addr(_ip.c_str());
        local.sin_addr.s_addr = INADDR_ANY;
        
        if (bind(_sockfd, (struct sockaddr*)&local, sizeof(local)) < 0) 
        {
            std::cerr << "bind error" << std::endl;

            return false; 
        }

        std::cout << "bind sucess" << std::endl;


        return true;
    }

#define SIZE 128
    void Start()
    {
        char buffer[SIZE];
        for ( ; ; )
        {
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            ssize_t size = recvfrom(_sockfd, buffer, sizeof(buffer) - 1, 0,  (struct sockaddr*)&peer, &len);
            if (size > 0)
            {
                buffer[size] = 0;
                int port = ntohs(peer.sin_port);
                std::string ip = inet_ntoa(peer.sin_addr);
                std::cout << ip << ":" << port << "# " << buffer << std::endl;

                std::string echo_msg = "server get!";
                echo_msg += buffer;

                sendto(_sockfd, echo_msg.c_str(), echo_msg.size(), 0, (struct sockaddr*)&peer, len);
            }
            else
            {
                std::cerr << "recvfrom error" << std::endl;
            }
        }
    }

    ~UdpServer()
    {}

};
