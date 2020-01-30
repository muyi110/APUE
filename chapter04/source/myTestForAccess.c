/*access函数的用法*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("usage: a.out <pathname>\n");
        exit(1);
    }
    if(access(argv[1], R_OK) < 0) // access 根据实际用户ID和组ID进行测试
    {
        printf("access error for %s\n", argv[1]);
        //exit(1);
    }
    else
        printf("read access OK\n");
    if(open(argv[1], O_RDONLY) < 0) // open 内核以进程有效用户ID和组ID为基础执行访问权限测试
    {
        printf("open error for %s\n", argv[1]);
        exit(1);
    }
    else
        printf("open for reading OK\n");
    exit(0);
}
