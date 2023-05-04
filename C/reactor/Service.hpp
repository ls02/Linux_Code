#pragma once 

#include "Reactor.hpp"
#include "Util.hpp"
#include "Service.hpp"
#include <cerrno>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>

#define ONCE_SIZE 128

// 1: 本轮读取全部完成
// -1: 读取出错
// 0: 对端关闭链接
static int RecverCore(int sock, std::string &inbuffer)
{
    while (true)
    {
        char buffer[ONCE_SIZE] = { 0 };
        ssize_t s = recv(sock, buffer, ONCE_SIZE, 0);
        if (0 < s)
        {
            // 读取成功
            buffer[s] = 0;

            inbuffer += buffer;
        }
        else if (0 > s)
        {
            if (errno == EINTR)
            {
                // IO信号被打断，概率特别低
                continue;
            }

            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                // 1. 读取完了，底层没数据了
                return 1; // success
            }

            // 2. 真出错了
            return -1;
        }
        else 
        {
            return 0;
        }

    }
}

int Recver(Event *evp)
{
    std::cout << "Recver  been called" << std::endl;
    // 1. 读取
    int result = RecverCore(evp->sock, evp->inbuffer);
    if (0 >= result)
    {
        // 差错处理
        if (evp->errorer)
        {
            evp->errorer(evp);
        }

        return -1;
    }
    // 2. 分包-- 一个或多个报文 解决粘包问题
    std::vector<std::string> tokens;
    std::string sep = "X";
    SplitSegment(evp->inbuffer, &tokens, sep);
    // 3. 反序列化 -- 针对一个报文 -- 提取有效参与计算或存储的信息
    for (auto &seg : tokens)
    {
        std::string data1, data2;
        
        // 和业务强相关
        if (Deserialize(seg, &data1, &data2)) 
        {
            // 4. 业务逻辑 -- 得到结果
            int x = atoi(data1.c_str());
            int y = atoi(data2.c_str());
            int z = x + y;

            // 5. 构建响应
            std::string res = data1;
            res += "+";
            res += data2;
            res += "=";
            res += std::to_string(z);
            res += sep;

            evp->outbuffer += res;
        }
    }
    // 6. 尝试直接或间接尽心发送
    if (!(evp->outbuffer).empty())
    {
        evp->R->EnaleRW(evp->sock, true, true);
    }
    
    return 0;
}

// 1: 全部数据发送完成
// 0: 数据没有发完但是不能再发了
// -1: 发送失败
int SenderCore(int sock, std::string &outbuffer)
{
    while (true)
    {
        int total = 0; // 累计本轮发送数据的量
        const char *start = outbuffer.c_str();
        int size = outbuffer.size();
        ssize_t curr = send(sock, start + total, size - total, 0);
        if (0 < curr)
        {
            total += curr;
            if (total == size)
            {
                //全部将数据发送完成
                outbuffer.clear();
                
                return 1;
            }
        }
        else
        {
            // 数据没有发完但是不能再发了
            if (errno == EINTR)
            {
                continue;
            }

            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                outbuffer.erase(0, total);

                return 0;
            }

            return -1;
        }
    }
}

int Sender(Event *evp)
{
    std::cout << "Sender  been called" << std::endl;
    int result = SenderCore(evp->sock, evp->outbuffer);

    if (1 == result)
    {
        evp->R->EnaleRW(evp->sock, true, false);
    }
    else if (0 == result)
    {
        evp->R->EnaleRW(evp->sock, true, true);
    }
    else 
    {
        if (evp->errorer)
        {
            evp->errorer(evp);
        }
    }
}

int Errorer(Event *evp)
{
    std::cout << "Errorer been called" << std::endl;
    evp->R->DeleteEvent(evp);
}
