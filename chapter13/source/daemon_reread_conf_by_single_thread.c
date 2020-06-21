/**********************************************************************
* 利用但线程实现守护进程重读配置文件
**********************************************************************/
#include <syslog.h>
#include <errno.h>
#include <stdlib.h>
#include "../../common/err_fucntions.h"

extern int lockfile(int);
extern int already_running(void);
extern void daemonize(const char *);

void reread(void)
{
    // 读取配置文件
}

void sigterm(int signo)
{
    syslog(LOG_INFO, "got SIGTERM; exiting");
    exit(0);
}

void sighup(int signo)
{
    syslog(LOG_INFO, "Re-reading configuration file");
    reread();
}

int main(int argc, char *argv[])
{
    char *cmd;
    struct sigaction sa;

    if((cmd = strrchr(argv[0], '/')) == NULL)
        cmd = argv[0];
    else
        cmd++;
    daemonize(cmd);

    if(already_running())
    {
        syslog(LOG_ERR, "daemon already running");
        exit(1);
    }
    // Handle signals of interrest
    sa.sa_handler = sigterm;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGHUP);
    sa.sa_flags = 0;
    if(sigaction(SIGTERM, &sa, NULL) < 0)
    {
        syslog(LOG_ERR, "can't catch SIGTERM: %s", strerroe(errno));
        exit(1);
    }
    sa.sa_handler = sighup;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGTERM);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP, &sa, NULL) < 0)
    {
        syslog(LOG_ERR, "can't catch SIGHUP: %s", strerror(errno));
        exit(1);
    }
    // Proceed with the rest of the daemon
    exit(0);
}
