/***********************************************************************
* 模拟实现标准库中的system函数(没有对信号进行处理)
***********************************************************************/
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int system(const char *cmdstring)
{
    pid_t pid;
    int status;

    if(cmdstring == NULL)
        return 1;              // 在unix系统上，system总是可用的

    if((pid = fork()) < 0)
    {
        status = -1;
    }
    else if(pid == 0)
    {
        execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
        _exit(127);
    }
    else
    {
        while(waitpid(pid, &status, 0) < 0)
        {
            if(errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }
    return status;
}

int main(int argc, char *argv[])
{
    int status;

    if((status = system("date")) < 0)
    {
        printf("system error\n");
    }
    if((status = system("nosuchcommand")) < 0)
    {
        printf("system error!\n");
    }
    return 0;
}
