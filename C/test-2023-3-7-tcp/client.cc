#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void Usage(std::string proc)
{
    std::cout << "Usage:\n\t" << proc << " server_ip server_port" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);

        exit(1);
    }

    std::string svr_ip = argv[1];
    uint16_t svr_port = (uint16_t)atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "socket fail" << std::endl;

        exit(2);
    }

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(svr_port);
    server.sin_addr.s_addr = inet_addr(svr_ip.c_str());

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        std::cerr << "connect fail" << std::endl;

        exit(3);
    }

    std::cout << "connect success!" << std::endl;

    while (true)
    {
        std::cout << "Please Enter# ";
        //std::string message;
        //getline(std::cin, message);
        char buffer[1024];
        fgets(buffer, sizeof(buffer) - 1, stdin);

        write(sockfd, buffer, strlen(buffer));

        ssize_t s = read(sockfd, buffer, sizeof(buffer) - 1);
        if (s > 0)
        {
            buffer[s] = 0;
            std::cout << "server echo# " << buffer << std::endl;
        }
    }

    return 0;
}
