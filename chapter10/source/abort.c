/************************************************************
* 符合POSIX.1规范的abort函数实现
* 进程终止时，系统会关闭所有打开的文件
************************************************************/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void abort(void)
{
    sigset_t mask;
    struct sigaction action;

    /* Caller can't ignore SIGABRT, if so reset to default */
    sigaction(SIGABRT, NULL, &action);
    if(action.sa_handler == SIG_IGN)
    {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }
    if(action.sa_handler == SIG_DFL)
        fflush(NULL);

    /* Caller can't block SIGARBT; make sure it's unblocked */
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT); // make has only SIGABRT turned off
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);

    /* if we're here, process caught SOGABRT and returned */
    fflush(NULL);
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    exit(1); /* this should never be executed */
}
