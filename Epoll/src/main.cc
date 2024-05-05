#include <memory>
#include "EpollSever.h"

int main()
{
    std::unique_ptr<EpollServer> server_ptr(new EpollServer(8899));
    server_ptr->Init();

    server_ptr->Start();

    return 0;
}