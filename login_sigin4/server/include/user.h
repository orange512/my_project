/*************************************************************************
	> File Name: user.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 14时56分52秒
 ************************************************************************/

#ifndef _USER_H
#define _USER_H
typedef struct user
{
    char name[32];
    unsigned char passwd[32];
    char other[960];
}user_t;
#endif
