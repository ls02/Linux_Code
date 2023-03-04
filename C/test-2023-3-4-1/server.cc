#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdlib.h>
#include <string.h>

const uint16_t port = 8083;

int main(void)
{
    //创建udp套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "sockfd failuer" << std::endl;

        return 1;
    }

    //进行端口绑定
    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        std::cerr << "bind failuer" << std::endl;

        return 2;
    }

    char buffer[1024] = { 0 };
    for ( ; ; )
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        ssize_t cnt = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&peer, &len);
        if (cnt > 0)
        {
            buffer[cnt] = 0;
            FILE* fp = popen(buffer, "r");
            if (fp == NULL)
            {
                std::cerr << "popen failuer" << std::endl;

                return 3;
            }

            std::string echo_buffer;
            char line[1024] = { 0 };
            while (fgets(line, sizeof(line) - 1, fp) != NULL)
            {
                echo_buffer += line;
            }
            
            pclose(fp);

            std::cout << "client: " << buffer << std::endl;
            sendto(sockfd, echo_buffer.c_str(), echo_buffer.size(), 0, (struct sockaddr*)&peer, len);

        }
        else 
        {
            std::cerr << "read failuer" << std::endl;
        } 
    }

    return 0;
}
