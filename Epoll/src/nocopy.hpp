#ifndef __NOCOPY_HPP__
#define __NOCOPY_HPP__

class NoCpy
{
public:
    // 构造禁用
    NoCpy() = delete;

    // 拷贝构造禁用
    NoCpy(const NoCpy &) = delete;

    const NoCpy &operator=(const NoCpy &) = delete;
};

#endif