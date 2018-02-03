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
#include"api_mysql.h"
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
    user = (struct user *)msg.val;
    printf("%s %s\n",user->name,user->passwd);

    MYSQL *mysql;
    mysql = init_mysql(mysql);
    mysql = connect_mysql(mysql,"192.168.0.128","root","950512","weChat");
    char command[1024];
    sprintf(command,"select * from usertable where uid = '%s' and passwd = '%s'; ",user->name,user->passwd);
    //query_mysql(mysql,"select *from usertable where uid = 'haha123' and passwd = '123';" );
    query_mysql(mysql,command);
    MYSQL_RES *result;
    result = import_result(mysql);
    int ret = count_result_rows(result);
    if(ret)
    {
        sprintf(command,"UPDATE usertable set cur_login_fd = '%d' where UID = '%s';",connfd,user->name);
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
    display_table_content(mysql,result);
    close_mysql(mysql);
    return 0;
}
