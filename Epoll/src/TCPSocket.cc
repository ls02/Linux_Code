#include "TCPSocket.h"

extern Log lg;

bool TCPSocket::CreateSocket()
{
    return Socket::CreateSocket(AF_INET, SOCK_STREAM, 0);
}

bool TCPSocket::ListenSocket(int backlog)
{
    if (listen(Socket::_sock_fd, backlog) < 0)
    {
        lg(Fatal, "Listen ERROR, %s: %d", strerror(errno), errno);

        return false;
    }

    return true;
}

int TCPSocket::Accept(std::string *client_ip, uint16_t *client_port)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    memset(&client, sizeof(client), 0);
    int client_sock = accept(Socket::_sock_fd, (struct sockaddr *)&client, &len);
    if (client_sock < 0)
    {
        lg(Fatal, "Accept ERROR, %s: %d", strerror(errno), errno);

        return -1;
    }

    // 获取成功填充ip和端口
    char ip_str[64]{0};
    inet_ntop(AF_INET, &client.sin_addr, ip_str, sizeof(ip_str));
    *client_ip = ip_str;
    *client_port = ntohs(client.sin_port);

    return client_sock;
}
bool TCPSocket::Connect(const std::string &ip, const uint16_t &port)
{
    struct sockaddr_in peer;
    memset(&peer, 0, sizeof(peer));
    peer.sin_family = AF_INET;
    peer.sin_port = htons(port);

    inet_pton(AF_INET, ip.c_str(), &(peer.sin_addr));

    int n = connect(_sock_fd, (struct sockaddr *)&peer, sizeof(peer));
    if (n == -1)
    {
        lg(Error, "Connect To %s:%d error", ip, port);

        return false;
    }

    return true;
}