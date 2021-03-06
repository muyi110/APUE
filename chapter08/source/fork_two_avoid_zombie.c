/************************************************************
 * fork两次避免僵尸进程，因为儿子进程先退出，孙子进程被init
 * 接管，与最初的父进程脱离关系
************************************************************/
#include "../../common/err_functions.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if(pid == 0)
    {
        if((pid = fork()) < 0)
            err_sys("fork error");
        else if(pid > 0)
        {
            printf("first child !!\n");
            exit(0);
        }
        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }
    printf("father\n");
    if(waitpid(pid, NULL, 0) != pid)
        err_sys("waitpid error");
    printf("WNOHANG: %d\n", WNOHANG);
    printf("WCONTINUED: %d\n", WCONTINUED);
    exit(0);
}
