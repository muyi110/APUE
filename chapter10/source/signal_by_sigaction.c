/*********************************************************
* 用sigaction函数实现signal函数
*********************************************************/
#include <signal.h>
#include <unistd.h>

typedef void Sigfunc(int);

Sigfunc * signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;
    
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if(signo == SIGALRM)
    {
    #ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT
    #endif
    }
    else
        act.sa_flags |= SA_RESTART;
    if(sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;
    return oact.sa_handler;
}

/*********************************************************
* 阻止被中断的系统调用重启动
* 除非说明了SA_RESTART标志，否则sigaction函数不再重启被
* 中断的系统调用
*********************************************************/
Sigfunc * signal_intr(int signo, Sigfunc *func)
{
    struct sigaction act, oact;
    
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT
#endif
    if(sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;
    return oact.sa_handler;
}
