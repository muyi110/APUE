/**********************************************************************
* 使用一个互斥量保护数据结构，此代码存在的缺点如下：
* 1 忽略了线程在调用foo_hold之前是如何找到对象的
* 2 如果另一个线程调用foo_hold阻塞等待互斥锁，即使在当前线程中判断该
对象的引用计数为0,foo_rele释放该对象内存依然是不对的
* 通过确保对象在释放内存前不会被找到来避免上述问题
**********************************************************************/
#include <stdio.h>
#include <pthread.h>

struct foo
{
    int f_count;
    pthread_mutex_t f_lock;
    int f_id;
};

struct foo *foo_alloc(int id)
{
    struct foo *fp;

    if((fp = malloc(sizeof(struct foo))) != NULL)
    {
        fp->f_count = 1;
        fp->f_id = id;
        if(pthread_mutex_init(&fp->f_lock, NULL) != 0)
        {
            free(fp);
            return NULL;
        }
    }
    return fp;
}

void foo_hold(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_lock);
    if(--fp->f_count == 0)
    {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }
    else
        pthread_mutex_unlock(&fp->lock);
}
