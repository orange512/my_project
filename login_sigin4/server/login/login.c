/*************************************************************************
	> File Name: login.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月31日 星期三 10时19分57秒
 ************************************************************************/

#include"login.h"
extern SQL_CONN_POOL *sp;
int login(int sockfd,msg_t msg)
{
    user_t *user;
    user =(user_t*)msg.val;
    printf("user->name:%s\n",user->name);
    printf("user->passwd:%s\n",user->passwd);
    msg_t ret_msg;
    SQL_NODE *lognode  = get_db_connect(sp);  
    if (NULL == lognode)  
    {  
        printf("get sql pool node error.\n");  
        return -1;  
    } 
    printf("--%d-- \n", lognode->index);
    printf("busy--%d--\n", sp->busy_number);
    char command[1024];
    sprintf(command,"select * from usertable where myname = '%s' and passwd = '%s';",user->name,user->passwd);
    query_mysql(&(lognode->fd),command);
    MYSQL_RES *result;
    result = import_result(&(lognode->fd));
    int ret = count_result_rows(result);
    if(ret)
    {
        ret_msg.key = sockfd;
    }
    else
        ret_msg.key = -1;
    write(sockfd,&ret_msg,sizeof(ret_msg));
    return 0;  

}
