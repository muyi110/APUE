/******************************************************
* 捕捉SIGUSR1和SIGUSR2的简单程序
******************************************************/
#include <stdio.h>
#include <unistd.h>
#include "../../common/err_functions.h"
#include <signal.h>

static void sig_usr(int);

int main(void)
{
    if(signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("can't catch SIGUSR1");
    if(signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("can't catch SIGUSR2");
    printf("sig_usr address: %ld\n", (long int)sig_usr);
    printf("signal back address: %ld\n", (long int)signal(SIGUSR1, sig_usr));
    for(;;)
        pause();
}

static void sig_usr(int signo)
{
    if(signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if(signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        err_dump("received signal %d\n", signo);
}
