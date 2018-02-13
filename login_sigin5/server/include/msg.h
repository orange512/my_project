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
#define PRIVATE_CHAT 3
#define EXIT 0
typedef struct msg
{
    int cmd;
    int key;
    int chat_sockfd;
    char val[1024];
}msg_t;

#endif
