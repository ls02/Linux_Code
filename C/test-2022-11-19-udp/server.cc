#include "server.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << "port" << std::endl;

        return -1;
    }

    int port = atoi(argv[1]);

    Server* svr = new Server(port);
    svr->InitUdpServer();
    svr->Start();

    return 0;
}
