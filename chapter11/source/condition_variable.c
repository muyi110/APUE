/***********************************************************************
* Shows an example of how to use a condition variable and a mutex together
to synchronize threads.
***********************************************************************/
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

void maketimeout(struct timespec *tsp, long minutes)
{
    struct timeval now;

    /* Get current time */
    gettimeofday(&now, NULL);
    tsp->tv_sec = now.tv_sec;
    tsp->tv_nsec = now.tv_usec * 1000;
    tsp->tv_sec += minutes * 60;
}

struct msg
{
    struct msg *m_next;
    /* ...more stuff here... */
};

struct msg *workq;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTGREAD_MUTEX_INITIALIZER;

void process_msg(void)
{
    struct msg *mp;

    for(;;)
    {
        pthread_mutex_lock(&qlock);
        while(workq == NULL)
            pthread_cond_wait(&qready, &qlock);
        mp = workq;
        workq = mp->m_next;
        pthread_mutex_unlock(&qlock);
        /* now process the message mp */
    }
}

void enqueue_msg(struct msg *mp)
{
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}
