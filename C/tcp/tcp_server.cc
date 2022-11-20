#include "tcp_server.hpp"

int main()
{
    TcpServer tsvr(8083);
    tsvr.InitTcpServer();
    tsvr.Loop();

    return 0;
}
