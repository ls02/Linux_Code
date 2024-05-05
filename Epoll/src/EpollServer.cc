#include "EpollSever.h"
#include <cstring>

uint32_t EVENT_IN = (EPOLLIN);
uint32_t EVENT_OUT = (EPOLLOUT);

void EpollServer::Init()
{
    _tcp_ptr->CreateSocket();
    _tcp_ptr->Bind(_port);
    _tcp_ptr->ListenSocket();

    lg(Info, "create listen socket Success! fd: %d", _tcp_ptr->GetFd());
}

void EpollServer::Dispatcher(struct epoll_event revs[], int num)
{
    // 开始轮询处理事件
    for (int i = 0; i < num; i++)
    {
        uint32_t events = revs[i].events;
        int fd = revs[i].data.fd;

        if (events & EVENT_IN)
        {
            // 读事件
            // 通过监听套接字来判断是链接事件还是读事件
            if (fd == _tcp_ptr->GetFd())
            {
                // 新链接事件
                Accepter();
            }
            else
            {
                // 读事件
                Recver(fd);
            }
        }
        else if (events & EVENT_OUT)
        {
            // 写事件
        }
        else
        {
            // 其他情况
        }
    }
}

void EpollServer::Accepter()
{
    // 获取一个新链接
    std::string client_ip;
    uint16_t client_port;

    int sock = _tcp_ptr->Accept(&client_ip, &client_port);
    if (sock > 0)
    {
        // 获取成功
        // 让epoll开始关心该套接字
        _epoll_ptr->EpollUpdate(EPOLL_CTL_ADD, sock, EPOLLIN);
        lg(Info, "Get a new Link, Client info@ %s:%d, fd is: %d", client_ip.c_str(), client_port, sock);
    }
}

void EpollServer::Start()
{
    // 添加listen 套接字到epoll当中让他进行监听
    _epoll_ptr->EpollUpdate(EPOLL_CTL_ADD, _tcp_ptr->GetFd(), EVENT_IN);
    struct epoll_event revs[defalut_num];
    for (;;)
    {
        sleep(1);
        int n = _epoll_ptr->EpollWait(revs, defalut_num);
        if (n > 0)
        {
            // 有事件就绪
            // 派发下去处理事件
            lg(Debug, "event happened, fd is : %d", revs[0].data.fd);
            Dispatcher(revs, n);
        }
        else if (n == 0)
        {
            lg(Info, "Time Out ...");
        }
        else
        {
            // 出错了
            lg(Error, "Epoll Wait Error");
        }
    }
}

void EpollServer::Recver(int fd)
{
    if (fd < 0)
    {
        lg(Error, "Invalid file descriptor: %d", fd);
        return;
    }

    char buffer[1024]{0};

    int ret = read(fd, buffer, sizeof(buffer) - 1);
    if (ret > 0)
    {
        // 读取到了数据
        buffer[ret] = 0;
        buffer[strcspn(buffer, "\r\n")] = 0;
        // 打印出来

        lg(Info, "Client-%d: %s", fd, buffer);
        std::string echo_str = "Server Echo: ";
        echo_str += buffer;
        write(fd, echo_str.c_str(), echo_str.size());

        if (!strcasecmp(buffer, "quit"))
        {
            // 客户端断开链接了，我们不需要关系和维护他的文件描述符
            _epoll_ptr->EpollUpdate(EPOLL_CTL_DEL, fd, 0);
            close(fd);
        }
    }
    else if (ret == 0)
    {
        // 客户端断开链接了
        lg(Info, "Client-%d quit ......", fd);
        // 客户端断开链接了，我们不需要关系和维护他的文件描述符
        _epoll_ptr->EpollUpdate(EPOLL_CTL_DEL, fd, 0);
        close(fd);
    }
    else
    {
        lg(Error, "recv error: fd is : %d", fd);
        // 读取出错了,我们不需要关系和维护他的文件描述符
        _epoll_ptr->EpollUpdate(EPOLL_CTL_DEL, fd, 0);
        close(fd);
    }
}