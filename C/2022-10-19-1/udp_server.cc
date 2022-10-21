#include "udp_server.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << "port" << std::endl;

        return 1;
    }

    int port = atoi(argv[1]);

    UdpServer* svr = new UdpServer(port);
    svr->InitUdpServer1();

    svr->Start();

    return 0;
}
