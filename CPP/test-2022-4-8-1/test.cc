#include <iostream>
#include <string>
#include <fstream>

int main(void)
{
    std::ofstream ofs("test.txt");
    std::ifstream ifs("test.cc");
    
    char ch = 0;
    while (ifs.get(ch))
    {
        ofs << ch;
    }

    return 0;
}
