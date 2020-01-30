/********************************************************************
 * vfork 函数示例，在子进程调用exec或者exit之前，内核使父进程处于休眠
 * 且在子进程调用exit或者exec之前，其在父进程空间中运行
********************************************************************/
#include "../../common/err_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 6;

int main(void)
{
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork\n");
    if((pid = vfork()) < 0)
    {
        err_sys("vfork error");
    }
    else if(pid == 0)
    {
        globvar++;
        var++;
        _exit(0);
    }
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);

    exit(0);
}
