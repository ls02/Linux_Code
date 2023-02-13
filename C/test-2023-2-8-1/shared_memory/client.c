#include "comm.h"

int main()
{
    //通过算法来生成唯一的key,再用这个key生成一个shmid
    key_t key = ftok(PATH_NAME, PROJ_ID);
    if (key < 0)
    {
        perror("ftok\n");

        return 1;
    }

    //获取共享内存ID
    int shmid = shmget(key, SIZE, IPC_CREAT);
    if (shmid < 0)
    {
        perror("shmid\n");

        return 2;
    }

    //关联共享内存
    char* mem = (char*)shmat(shmid, NULL, 0); 

    //向共享内存写入数据
    
    int i = 0;
    while (i < 5)
    {
        sleep(1);
        mem[i] = 'a';
        i++;
        mem[i] = 0;
    }

    sleep(10);

    shmdt(mem);

    return 0;
}
