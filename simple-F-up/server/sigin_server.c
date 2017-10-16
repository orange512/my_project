/*************************************************************************
	> File Name: play.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月29日 星期五 20时16分42秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include"msg.h"
#include"user.h"
int sigin_server(int connfd,struct msg msg)
{
    int ret;
    struct msg ret_msg;//回复给客户端
    memset(&ret_msg,0,sizeof(ret_msg));
    struct user *user;
    user = (struct user *)msg.val;
    printf("%s %s %d %d\n",user->name,user->passwd,user->type,user->flag);
    
    FILE *fp = NULL;
    fp = fopen("passwd.dat","a+");
    if(fp == NULL)
    {
        perror("fopen");
        ret_msg.key = -1;
        write(connfd,&ret_msg,sizeof(ret_msg));
        return -1;
    }
    ret = fprintf(fp,"%s %s %d %d\n",user->name,user->passwd,user->type,user->flag);
    if(ret < 0)
    {
        perror("fprintf");
        ret_msg.key = -2;
        write(connfd,&ret_msg,sizeof(ret_msg));
    }
    ret_msg.key = 1;
    write(connfd,&ret_msg,sizeof(ret_msg));
    return 0;
}

