/*****************************************************************
* alarm 函数对阻塞操作设置时间上限
*****************************************************************/
#include <setjmp.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "../../common/err_functions.h"

#define MAXLINE 512

static void sig_alrm(int);
static jmp_buf env_alrm;

int main(void)
{
    int n;
    char line[MAXLINE];

    if(signal(SIGALRM, sig_alrm) == SIG_ERR)
        err_sys("signal(SIGALRM) error");
    if(setjmp(env_alrm) != 0)
        err_quit("read timeout");
    alarm(10);
    if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
    {
        if(errno == EINTR)
            printf("read interrupted\n");
        err_sys("read error");
    }
    alarm(0);
    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void sig_alrm(int signo)
{
    printf("get alarm signal\n");
    longjmp(env_alrm, 1);
}
