/*************************************************************************
	> File Name: login.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月29日 星期五 20时15分04秒
 ************************************************************************/

#include<stdio.h>
#include"msg.h"
#include<string.h>
#include"user.h"
#include<unistd.h>

//key
// -1 open
// -2 name
// -3 passwd
// -4 flag
int login_server(int connfd,struct msg msg)
{
    struct msg ret_msg = {0};//回复给客户端
    memset(&ret_msg,0,sizeof(ret_msg));
    struct user *user;
    struct user tmp;//将文件信息存储到tmp里
    user = (struct user *)msg.val;
    int filename = 0;//标记错误
    int passwd = 0;
    int flag = 0;
    printf("%s %s\n",user->name,user->passwd);
    
    FILE *fp = NULL;
    fp = fopen("passwd.dat","r");
    if(fp == NULL)
    {
        perror("fopen");
        ret_msg.key = -1;
        write(connfd,&ret_msg,sizeof(ret_msg));
        return -1;
    }
    while( (fscanf(fp,"%s %s %d %d\n",tmp.name,tmp.passwd,&tmp.type,&tmp.flag)) != EOF)
    {
        filename = 0;
        passwd = 0;
        if(!strcmp(user->name,tmp.name))
        {
            filename = 1;
            if(!strcmp(user->passwd,tmp.passwd))
            {
                passwd = 1;
                if(tmp.flag == 1)
                {
                    flag = 1;
                    break;
                }
            }
        }

    }
    if(filename == 0)
    {
        ret_msg.key = -2;
    }
    if(filename == 1 && passwd == 0)
    {
        ret_msg.key = -3;
    }
    if(filename == 1 && passwd == 1 && flag == 0)
    {
        ret_msg.key = -4;
    }
    if(filename == 1 && passwd == 1 && flag == 1)
    {
        ret_msg.key = 1;
    }
    write(connfd,&ret_msg,sizeof(ret_msg));
    return 0;
}
