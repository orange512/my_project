/*************************************************************************
	> File Name: msg.h
	> Author: 
	> Mail: 
	> Created Time: 2017年09月29日 星期五 19时35分48秒
 ************************************************************************/

#ifndef _MSG_H
#define _MSG_H
//cmd
#define USER_MODULE 1
#define PLAY_MODULE 2
#define UP_MODULE 3

struct msg
{
    int cmd;
    int key;
    char val[128];
};
#endif
