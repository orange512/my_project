/*************************************************************************
	> File Name: msg.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 14时52分59秒
 ************************************************************************/

#ifndef _MSG_H
#define _MSG_H
#define SIGIN 1
#define LOGIN 2
#define EXIT 3
typedef struct msg
{
    int cmd;
    int key;
    char val[1024];
}msg_t;

#endif
