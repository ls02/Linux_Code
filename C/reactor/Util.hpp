#pragma once 

#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <fcntl.h>
// 工具类

void SetNoBlock(int sock)
{
    int fl = fcntl(sock, F_GETFL);
    if (0 > fl)
    {
        std::cerr << "fcntl failed" << std::endl;

        return;
    }

    fcntl(sock, F_SETFL, fl | O_NONBLOCK);
}

void SplitSegment(std::string &inbuffer, std::vector<std::string> *tokns, std::string sep)
{
    while (true)
    {
        auto pos = inbuffer.find(sep);
        if (pos == std::string::npos)
        {
            break;
        }

        std::string sub = inbuffer.substr(0, pos);
        tokns->push_back(sub);
        inbuffer.erase(0, pos + sep.size());
    }
}

bool Deserialize(const std::string &seg, std::string *out1, std::string *out2)
{
    std::string op = "+";
    auto pos = seg.find(op);
    if (pos == std::string::npos)
    {
        return false;
    }

    *out1 = seg.substr(0, pos);
    *out2 = seg.substr(pos + op.size());

    return true;
}
