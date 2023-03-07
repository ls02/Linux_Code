#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Task.hpp"
#include "ThreadPool.hpp"

const uint16_t port = 8083;

void ServiceIo(int new_sock)
{
    while (true)
    {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        ssize_t s = read(new_sock, buffer, sizeof(buffer) - 1);
        if (s > 0)
        {
            buffer[s - 1] = 0;

            std::cout << "client# " << buffer << std::endl;

            std::string echo_string = ">>>server<<<, ";
            echo_string += buffer;
            write(new_sock, echo_string.c_str(), echo_string.size());
        }
        else if (s == 0)
        {
            std::cout << "clinet quit ..." << std::endl;

            break;
        }
        else 
        {
            std::cerr << "read error" << std::endl;

            break;
        }
    }
}

void ServiceChild(int new_sock)
{
    pid_t id = fork();
    
    if (id > 0)
    {
        waitpid(id, nullptr, 0);
        close(new_sock);
    }
    else if (id == 0)
    {
        if (fork() > 0)
        {
            exit(1);
        }

        ServiceIo(new_sock);
        close(new_sock);
        exit(1);
    }
}

void* HandlerRequest(void* args)
{
    pthread_detach(pthread_self());
    int sock = *(int*)args;
    delete (int*)args;

    ServiceIo(sock);
    close(sock);
}

void ServiceThread(int new_sock)
{
    pthread_t tid;

    int* pram = new int(new_sock);
    pthread_create(&tid, nullptr, HandlerRequest, pram);
}

void Usage(std::string proc)
{
    std::cout << "Usage: " << proc << " port" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);

        exit(4);
    }

    int listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock < 0)
    {
        std::cerr << "socket fail" <<  std::endl;

        exit(1);
    }

    struct sockaddr_in local;
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[1]));
    local.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSock, (struct sockaddr*)&local, sizeof(local)) < 0)
    {
        std::cerr << "bind fail" << std::endl;

        exit(2);
    }

    const int backLog = 5;
    if (listen(listenSock, backLog) < 0)
    {
        std::cerr << "listen fail" << std::endl;

        exit(3);
    }

    for ( ; ; )
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int new_sock = accept(listenSock, (struct sockaddr*)&peer, &len);
        if (new_sock < 0)
        {
            continue;
        }
        uint16_t cli_port = ntohs(peer.sin_port);
        std::string cli_ip = inet_ntoa(peer.sin_addr);

        std::cout << "Get a new link -> : [" << cli_ip << " : " << cli_port << "]#" << new_sock << std::endl;

        //ServiceChild(new_sock);
        //ServiceThread(new_sock);
        ns_task::Task t(new_sock);

        ns_threadpool::ThreadPool<ns_task::Task>::GetInstance()->PushTask(t);

    }

    return 0;
}
