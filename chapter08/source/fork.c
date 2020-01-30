/******************************************************************
 * fork 函数示例，子进程对变量的改变并不影响父进程中该变量的值
******************************************************************/
#include "../../common/err_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globvar = 6; // 在初始化数据段的变量
char buf[] = "a write to stdout\n";

int main(void)
{
    int var; // 在栈上的自动变量
    pid_t pid;

    var = 88;
    if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
    {
        err_sys("write error");
    }
    printf("before fork\n");

    if((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if(pid == 0) // 子进行修改变量
    {
        globvar++;
        var++;
    }
    else              // 父进程
        sleep(2);
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}
