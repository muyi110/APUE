/**************************************************************
* 测试调用解释器程序
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        if(execl("./testinterp", "myarg1", "MY ARG2", (char*)0) < 0)
        {
            printf("execl error\n");
        }
        exit(0);
    }
    if(waitpid(pid, NULL, 0) < 0)
    {
        printf("waitpid error\n");
    }
    return 0;
}
