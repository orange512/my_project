/*************************************************************************
	> File Name: file_module.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 17时47分11秒
 ************************************************************************/
#include<stdio.h>
#include"msg.h"
#include"file_module.h"
int file_module(int connfd,struct msg msg)
{
    switch(msg.key)
    {
        case 1:
        up_file(connfd,msg);
        break;
        case 2:
        down_file(connfd,msg);
        default:
        break;
    }
    return 0;
}
