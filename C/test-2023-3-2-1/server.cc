#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

const uint16_t port = 8083;

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "sockfd" << std::endl;

        return 1;
    }

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        std::cerr << "bind" << std::endl;
        
        return 2;
    }

    bool flags = false;

    char buffer[1024];
    while (!flags)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);

        recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&peer, &len);

        std::cout << "client# " << buffer << std::endl;;

        std::string str;
        std::cout << "请输入: ";
        std::cin >> str;
        sendto(sockfd, str.c_str(), str.size(), 0, (struct sockaddr*)&peer, len);
    }

    return 0;
}
