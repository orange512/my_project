/*************************************************************************
	> File Name: chat_module.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月25日 星期四 10时49分34秒
 ************************************************************************/

#include<stdio.h>
#include"msg.h"
int chat_module(int connfd,struct msg msg)
{
    switch(msg.key)
    {
        case 1:
        group_chat(connfd,msg);
        break;
        case 2:
        p2p_chat(connfd,msg);
        break;
        case 3:
        luckey_money(connfd,msg);
        break;
        default:
        break;
    }
    return 0;
}
