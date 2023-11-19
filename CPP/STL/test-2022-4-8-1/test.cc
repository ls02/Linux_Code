#include <iostream>
#include <string.h>
#include <string>
#include <fstream>

int main(void)
{
    std::ofstream ofs("test.bin");
    
    //char ch = 0;
    //while (ifs.get(ch))
    //{
    //    ofs<< ch;
    //}

    const char* str = "hello";
    ofs.write(str, strlen(str));
    
    std::ifstream ifs("test.bin");
    char* s = new char[strlen(str)];
    ifs.read(s, strlen(str)); 
    std::cout << s << std::endl;

    return 0;
}
