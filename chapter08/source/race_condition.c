/***************************************************************
*  演示输出竞争条件
***************************************************************/
#include <stdio.h>
#include <unistd.h>

static void charatatime(char*);

int main(int argc, char* argv[])
{
    pid_t pid;
    
    if((pid = fork()) < 0)
    {
        printf("fork error");
    }
    else if(pid == 0)
    {
        charatatime("output from child\n");
    }
    else
    {
        charatatime("output from parent\n");
    }
    return 0;
}

static void charatatime(char *str)
{
    char *ptr;
    int c;

    setbuf(stdout, NULL); // 标准输出设置无缓冲
    for(ptr = str; (c = *ptr) != 0; ++ptr)
    {
        putc(c, stdout);
    }
}
