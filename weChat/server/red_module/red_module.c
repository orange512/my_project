/*************************************************************************
	> File Name: red_module.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 17时59分47秒
 ************************************************************************/

#include<stdio.h>
#include"msg.h"
#include"red_module.h"
int red_module(int connfd,struct msg msg)
{
    switch(msg.key)
    {
        case 1:
        send_packet(connfd,msg);
        break;
        case 2:
        recv_packet(connfd,msg);
        break;
        default:
        break;
    }
}
