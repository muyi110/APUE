/*创建两个文件，第一个文件umask值为0, 第二个文件umask值禁止组和其他用户访问权限*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(void)
{
    umask(0);
    if(creat("foo", RWRWRW) < 0)
    {
        printf("creat error for foo\n");
        exit(1);
    }
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if(creat("bar", RWRWRW) < 0)
    {
        printf("creat error for bar\n");
        exit(1);
    }
    exit(0);
}
