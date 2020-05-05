/**************************************************************
* sigaddset, sigdelset和sigismember信号集函数实现
* 假设有31种信号，用一个整型表示，每一位代表一位信号
* 不存在编号为0的信号，所需需要减1得到信号的位编号数
**************************************************************/
#include <signal.h>
#include <errno.h>

#define sigemptyset(ptr)   (*(ptr) = 0)
#define sigfillset(ptr)    (*(ptr) = ~(sigset_t)0, 0)

#define SIGBAD(signo)  ((signo) <= 0 || (signo) >= NSIG)

int sigaddset(sigset_t *set, int signo)
{
    if(SIGBAD(signo))
    {
        errno = EINVAL;
        return -1;
    }
    *set |= 1 << (signo - 1);
    return 0;
}

int sigdelset(sigset_t *set, int signo)
{
    if(SIGBAD(signo))
    {
        errno = EINVAL;
        return -1;
    }
    *set &= ~(1 << (signo - 1));
    return 0;
}

int sigismember(sigset_t *set, int signo)
{
    if(SIGBAD(signo))
    {
        errno = EINVAL;
        return -1;
    }
    return ((*set & (1 << (signo - 1))) != 0);
}
