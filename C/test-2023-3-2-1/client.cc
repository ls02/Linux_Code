#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void Usage(std::string proc)
{
    std::cout << "Usage: \n\t" << proc << "server_ip server_prot" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);

        return 0;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "sockfd" << std::endl;

        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    while (true)
    {
        std::string str;
        std::cout << "请输入:";
        std::cin >> str;

        sendto(sockfd, str.c_str(), str.size(), 0, (struct sockaddr*)&server, sizeof(server));

        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        char buffer[1024];
        recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&temp, &len);
        std::cout << "server: " << buffer << std::endl;
    }

    return 0;
}
