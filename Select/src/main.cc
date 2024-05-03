#include <iostream>
#include "Select.hpp"
#include <memory>

int main()
{
    std::unique_ptr<SelectServer> server(new SelectServer);
    server->Init();
    server->Start();

    return 0;
}