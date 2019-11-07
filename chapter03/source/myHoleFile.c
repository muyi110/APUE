#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;

    if((fd = creat("file.hole", 777)) < 0)
    {
        printf("creat error\n");
        exit(1);
    }
    if(write(fd, buf1, 10) != 10)
    {
        printf("buf1 write error");
        exit(1);
    }
    /*现在文件偏移量是10*/
    if(lseek(fd, 16384, SEEK_SET) == -1)
    {
        printf("lseek error");
        exit(1);
    }
    /*现在文件偏移量是16384*/
    if(write(fd, buf2, 10) != 10)
    {
        printf("buf2 write error");
        exit(1);
    }
    /*现在文件偏移量是16394*/
}
