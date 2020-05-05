/***************************************************************
* 打印进程信号屏蔽字中的信号名
****************************************************************/
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include "../../common/err_functions.h"

void pr_mask(const char* str)
{
    sigset_t sigset;
    int errno_save;

    errno = errno_save;
    if(sigprocmask(0, NULL, &sigset) < 0)
    {
        err_ret("sigprocmask error");
    }
    else // add signal here
    {
        printf("%s", str);
        if(sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if(sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if(sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");
        if(sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        printf("\n");
    }
    errno = errno_save;
}
