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
#include"api_mysql.h"
int sigin_server(int connfd,struct msg msg)
{
    long ret;
    struct msg ret_msg;//回复给客户端
    memset(&ret_msg,0,sizeof(ret_msg));
    struct user *user;
    user = (struct user *)msg.val;
    printf("%s %s %d %d\n",user->name,user->passwd,user->type,user->flag);
    
    /*FILE *fp = NULL;
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
    }*/
    
    MYSQL *mysql;
    mysql = init_mysql(mysql);
    mysql = connect_mysql(mysql,"192.168.0.128","root","950512","weChat");
    char command[1024];
    sprintf(command,"insert into usertable(uid,uname,passwd) values('%s','null','%s'); ",user->name,user->passwd);
    //query_mysql(mysql,"select *from usertable where uid = 'haha123' and passwd = '123';" );
    query_mysql(mysql,command);
    ret = affected_rows(mysql);
    if(ret)
    {
        sprintf(command,"UPDATE usertable set islogin = 1 where UID = '%s';",user->name);
        query_mysql(mysql,command);
        ret = affected_rows(mysql);
        if(!ret)
        {
            printf("%s登录失败\n",user->name);
            ret_msg.key = -1;
        }
        ret_msg.key = 1;
    }
    else
        ret_msg.key = -1;
    write(connfd,&ret_msg,sizeof(ret_msg));
    close_mysql(mysql);
    write(connfd,&ret_msg,sizeof(ret_msg));
    return 0;
}

