/*********************************************************************
 * 向标准错误输出一条错误消息
 ********************************************************************/
#include <errno.h>
#include <stdarg.h> /* 定义va_list变量，va_start，va_arg，va_end等宏*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 4096
static void err_doit(int, int, const char*, va_list);

/* Nonfatal error related to a system call */
void err_ret(const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}

/* Fatal error related to a system call */
void err_sys(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

/* Nonfatal error unrelated to a system call */
void err_cont(int error, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
}

/* Fatal error unrelated to a system call */
void err_exit(int error, const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}

/* Fatal error related to a system call */
void err_dump(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    abort(); // dump core and terminate
    exit(1);
}

/* Nonfatal error unrelated to a system call */
void err_msg(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}

/* Fatal error unrelated to a system call */
void err_quit(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}

/* Print a message and return to caller */
static void err_doit(int errnoflag, int error, const char* fmt, va_list ap)
{
    char buf[MAXLINE];
    vsnprintf(buf, MAXLINE-1, fmt, ap);
    if(errnoflag)
    {
        snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
    }
    strcat(buf, "\n");
    fflush(stdout);
    fputs(buf, stderr);
    fflush(NULL);
}
