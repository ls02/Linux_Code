#include "client.hpp"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage:" << argv[0] << " server_ip server_port" << std::endl;

        return -1;
    }

    std::string ip = argv[1];
    int port = atoi(argv[2]);

    Client* cli = new Client(port, ip);
    cli->InitClient();
    cli->Start();

    return 0;
}
