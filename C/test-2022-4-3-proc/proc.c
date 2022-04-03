#include "proc.h"

void proc(void)
{
    char str[101]  = { 0 };
    const char* pStr = "/-\\";
    int i = 0;

    while (i < 101)
    {
        printf("[%-100s][%c][%d%%]\r", str, pStr[i % 4], i);
        fflush(stdout);
        str[i++] = '#';
        usleep(10000);         
    }

    printf("\n");
}
