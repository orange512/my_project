/*************************************************************************
	> File Name: user_module.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月29日 星期五 19时50分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"msg.h"
#include"user_module.h"
int user_module(int connfd,struct msg msg)
{
    switch(msg.key)
    {
        case 1:
        login_server(connfd,msg);
        //登录
        break;
        case 2:
        //注册
        sigin_server(connfd,msg);
        break;
        case 3:
        //忘记密码
        break;
        default:
        printf("%s,msg.key = %d,msg.val = %s\n",__func__,msg.key,msg.val);
    }
    return 0;
}
