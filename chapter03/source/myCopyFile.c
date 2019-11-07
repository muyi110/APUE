/*调用read和write实现复制文件*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 4096

int main(void)
{
    int n;
    char buf[BUFFSIZE];

    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        if(write(STDOUT_FILENO, buf, n) != n)
        {
            printf("write error\n");
            exit(1);
        }
    }
    if(n < 0)
    {
        printf("read error\n");
        exit(1);
    }
    exit(0);
}
