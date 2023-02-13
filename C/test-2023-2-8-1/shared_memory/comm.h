#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MY_FIFO "./fifo"
#define SIZE 4096
#define PROJ_ID 0x5555
#define PATH_NAME "./"
