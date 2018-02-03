/*************************************************************************
	> File Name: user.h
	> Author: 
	> Mail: 
	> Created Time: 2017年09月29日 星期五 20时21分15秒
 ************************************************************************/

#ifndef _USER_H
#define _USER_H
#define USER 1
#define ROOT 2

struct user
{
    char name[60];
    char passwd[60];
    int type;
    int flag;
};
#endif
