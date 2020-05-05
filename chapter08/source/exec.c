/***************************************************************
* exec类函数测试
***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

/*模拟环境变量表，以NULL 结尾*/
char *env_init[] = {"UESR=unknow", "PATH=/tmp", NULL};

int main(int argc, char *argv[])
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        if(execle("./echoall", "echoall", "myarg1", "MY ARG2", (char*)0, env_init) < 0)
        {
            printf("execle error\n");
        }
        exit(0);
    }
    if(waitpid(pid, NULL, 0) < 0)
    {
        printf("waitpid error\n");
    }

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        if(execlp("echoall", "echoall", "only 1 arg", (char*)0, env_init) < 0)
        {
            printf("execlp error\n");
        }
        exit(0);
    }
    printf("parent process over!!\n");
    exit(0);
}
