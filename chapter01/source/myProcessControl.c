/*
 * 功能：从标准输入读取命令，然后执行（类似shell）
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define MAXLINE 4096

int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while(fgets(buf, MAXLINE, stdin) != NULL) // fgets() 从标准输入一次读取一行
    {
        if(buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = 0;
        }
        if((pid = fork()) < 0)
        {
            printf("fork error");
            exit(0);
        }
        else if(pid == 0) // child
        {
            execlp(buf, buf, (char*)0);
            printf("couldn't execute: %s", buf);
            exit(127);
        }
        if((pid = waitpid(pid, &status, 0)) < 0)
        {
            printf("waitpid error");
            exit(0);
        }
        printf("%% ");
    }
    exit(0);
}
