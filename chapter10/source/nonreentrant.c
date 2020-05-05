/*************************************************************
* 在信号处理程序中调用不可重入函数
*************************************************************/
#include <pwd.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "../../common/err_functions.h"

static void my_alarm(int signo)
{
    struct passwd *rootptr;

    printf("in signal handle\n");
    if((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root) error");
    alarm(1);
}

int main(void)
{
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    for(;;)
    {
        if((ptr = getpwnam("yangliuqing")) == NULL)
            err_sys("getpwnam error");
        if(strcmp(ptr->pw_name, "yangliuqing") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }
}
