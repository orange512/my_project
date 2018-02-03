/*************************************************************************
	> File Name: condition.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月18日 星期三 17时28分29秒
 ************************************************************************/

#ifndef _CONDITION_H
#define _CONDITION_H
#include<pthread.h>
typedef struct condition
{
    pthread_mutex_t pmutex;
    pthread_cond_t pcond;
}condition_t;

int condition_init(condition_t *cond);
int condition_lock(condition_t *cond);
int condition_unlock(condition_t *cond);
int condition_wait(condition_t *cond);
int condition_timedwait(condition_t *cond,const struct timespec *abstime);
int condition_signal(condition_t *cond);
int condition_broadcast(condition_t *cond);
int condition_destroy(condition_t *cond);
#endif
