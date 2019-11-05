/*
 * 功能：从标准输入读取命令，然后执行（类似shell）
 *       自定义捕捉信号
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define MAXLINE 4096

static void sig_int(int); // 信号捕捉函数

int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    if(signal(SIGINT, sig_int) == SIG_ERR)
    {
        printf("signal error");
        exit(127);
    }

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

void sig_int(int signo)
{
    printf("interrupt\n%%");
}
