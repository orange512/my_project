/*************************************************************************
	> File Name: chat_module.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 17时52分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"msg.h"
#include"chat_module.h"
int chat_module(int connfd,struct msg msg)
{
    switch(msg.key)
    {
        case 1:
        group_chat(connfd,msg);
        break;
        case 2:
        private_chat(connfd,msg);
        break;
        default:
        break;
    }
}
