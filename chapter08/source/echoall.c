/***************************************************************
* 用于生成一个可执行文件，被exec.c程序调用
***************************************************************/
#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    char **ptr;
    extern char **environ;

    for(i = 0; i < argc; ++i)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    for(ptr = environ; *ptr != 0; ++ptr)
    {
        printf("%s\n", *ptr);
    }
    return 0;
}
