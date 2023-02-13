#include "comm.h"

int main()
{
   int fd = open(MY_FIFO, O_WRONLY); 
   if (fd < 0)
   {
       perror("open\n");
       
       return 1;
   }

   //写入业务
    while (1)
    {
        char str[1024] = { 0 };
        printf("请输入:");
        fflush(stdout);
        ssize_t s = read(0, str, sizeof(str) - 1);
        if (s > 0)
        {
            str[s - 1] = 0;
            printf("client: %s\n", str);

            write(fd, str, strlen(str));
        }
    }

   close(fd);

   return 0;
}
