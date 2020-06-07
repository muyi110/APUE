/***************************************************************************
* genenv 三个实现，从线程不安全到线程安全版本（可重入）
***************************************************************************/
/*线程不安全的版本*/
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXSTRINGSZ 4096

static char envbuf[MAXSTRINGSZ];
extern char **environ;
pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
static pthread_key_t key;
pthread_mutex_t env_mutex_t = PTHREAD_MUTEX_INITIALIZER;

char *getenv(const char *name)
{
    int i, len;

    len = strlen(name);
    for(i = 0; environ[i] != NULL; ++i)
    {
        if((strncmp(name, environ[i], len) == 0) && (environ[i][len] == "="))
        {
            strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
            return envbuf;
        }
    }
    return NULL;
}

/*线程安全版本1*/
static void thread_init(void)
{
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf, int buflen)
{
    int i, len, olen;

    pthread_once(&init_done, thread_init);
    len = strlen(name);
    pthread_mutex_lock(&env_mutex);
    for(i = 0; environ[i] != NULL; ++i)
    {
        if((strncmp(name, environ[i], len) == 0) && (environ[i][len] == "="))
        {
            olen = strlen(&environ[i][len+1]);
            if (olen >= buflen)
            {
                pthread_mutex_unlock(&env_mutex);
                return ENOSPC;
            }
            strcpy(buf, &environ[i][len+1]);
            pthread_mutex_unlock(&env_mutex);
            return 0;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return ENOENT;
}

/*线程安全版本2，使用线程特定数据结构*/
static void thread_init(void)
{
    pthread_key_create(&key, free);
}

char *getenv_t(const char *name)
{
    int i, len;
    char *envbuf;

    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex_t);
    envbuf = (char *)pthread_getspecific(key);
    if(envbuf == NULL)
    {
        envbuf = malloc(MAXSTRINGSZ);
        if(envbuf == NULL)
        {
            pthread_mutex_unlock(&env_mutex_t);
            return NULL;
        }
        pthread_setspecific(key, envbuf);
    }
    len = strlen(name);
    for(i = 0; environ[i] != NULL; ++i)
    {
        if((strncmp(name, environ[i], len) == 0) && (environ[i][len] == "="))
        {
            strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
            pthread_mutex_unlock(&env_mutex_t);
            return envbuf;
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return NULL;
}
