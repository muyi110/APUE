/******************************************************
打印系统的环境变量
******************************************************/
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int main(int argc, char *argv[])
{
    char **env = environ;
    for(int i = 0; env[i] != NULL; ++i)
    {
        printf("env[%d]: %s\n", i, env[i]);
    }
    return 0;
}
