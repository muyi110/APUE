/*chmod函数的测试*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(void)
{
    struct stat statbuf;

    if(stat("foo", &statbuf) < 0)
    {
        printf("stat error for foo.\n");
        exit(1);
    }
    /*打开 set-group-ID and turn off group-execute*/
    if(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
    {
        printf("chmod error for foo.\n");
        exit(1);
    }
    /*设置mode为rw-r--r--*/
    if(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
    {
        printf("chmod error for bar.\n");
        exit(1);
    }
    exit(0);
}
