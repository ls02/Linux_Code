#include "comm.h"

int main()
{
    //通过ftok生成一个唯一 key
    key_t key = ftok(PATH_NAME, PROJ_ID);
    if (key < 0)
    {
        perror("ftok\n");

        return 1;
    }

    //获得shmid
    //如果存在就返回当前的共享内存，如果不存在就创建并且得到一个最新的没有人使用过的
    int shmid = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid < 0)
    {
        perror("shmid\n");

        return 2;
    }
    //将进程和共享内存关联
    char* mem = (char*)shmat(shmid, NULL, 0);
    
    //业务逻辑区
    while (1)
    {
        sleep(1);
        printf("%s\n", mem);
    }

    //去关联
    shmdt(mem);

    //把共享内存从内核区删掉
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
