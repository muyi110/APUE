/*实现和dup2功能相同的函数，不使用fcntl函数，有正确的出错处理*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "exercise2.h"

int myDup2(int fd, int newfd)
{
    long openmax = open_max(); // 来源于chapter02，获取OPEN_MAX
    int index = 0;
    int fdarray[newfd];
    if(newfd < 0 || newfd > openmax-1)
    {
        printf("invalid newfd");
        return -1;
    }
    if((fdarray[index] = dup(fd)) == -1) // 测试fd文件描述符是否是打开的
    {
        printf("dup function error.\n");
        return -1;
    }
    else
    {
        close(fdarray[index]);
    }
    if(newfd == fd) // newfd == fd的情况
        return fd;
    // 如果newfd打开则将其关闭
    if(dup(newfd) != -1)
    {
        int res = close(newfd);
        if(res == -1)
        {
            printf("close error");
            return -1;
        }
    }
    // 复制文件描述符号
    for(index = 0; index < newfd; ++index)
    {
        fdarray[index] = dup(fd); // dup返回当前可用文件描述符中最小值
        if(fdarray[index] == -1)
        {
            printf("dup function error.\n");
            return -1;
        }
        else
        {
            if(fdarray[index] == newfd)
                break;
        }
    }
    // 关闭之前打开的文件描述符号
    for(index = 0; index < newfd; ++index)
    {
        if(fdarray[index] == newfd)
            return newfd;
        else if(close(fdarray[index]) == -1)
        {
            printf("close error.\n");
            return -1;
        }
    }
    return newfd;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("params error.");
        exit(1);
    }
    int newfd = atoi(argv[1]);
    int fd = open(argv[2], 0);
    if(fd == -1)
    {
        printf("open error");
        exit(1);
    }
    int return_fd = myDup2(fd, newfd);
    printf("new fd is: %d\n", return_fd);
    if(close(fd) == -1 || close(return_fd) == -1)
    {
        printf("close error\n");
        exit(1);
    }
    exit(0);
}
