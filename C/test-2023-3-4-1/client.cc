#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void Usage(const char* porc)
{
    std::cout << "Usage:\n\t" << porc << "server_ip server_port" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);

        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        std::cout << "sockfd failuer" << errno << std::endl;

        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    for ( ; ; )
    {
        std::cout << "请输入：";
        std::string message;
        getline(std::cin, message);
        sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&server, sizeof(server));

        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        char buffer[1024] = { 0 };
        ssize_t cnt = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&temp, &len);
        if (cnt > 0)
        {
            buffer[cnt] = 0;
            std::cout << buffer << std::endl;
        }
    }

    return 0;
}
