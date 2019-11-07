/*对于一个文件描述符号设置一个或多个文件状态标志*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void set_fl(int fd, int flags) // flags是要打开的文件状态标志
{
    int val;
    
    // step1: 获取原有的标志
    if((val = fcntl(fd, F_GETFL, 0)) < 0)
    {
        printf("fcntl F_GETFL error");
        exit(1);
    }
    // step2: 设置新的标志
    val |= flags;
    if(fcntl(fd, F_SETFL, val) < 0)
    {
        printf("fcntl F_SETFL error");
        exit(1);
    }
    exit(0);
}
