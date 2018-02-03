/*************************************************************************
	> File Name: login.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月31日 星期三 10时19分57秒
 ************************************************************************/

#include"login.h"
int login(int sockfd,msg_t msg)
{
    user_t *user;
    user =(user_t*)msg.val;
    printf("user->name:%s\n",user->name);
    printf("user->passwd:%s\n",user->passwd);
    msg_t ret_msg;
    SQL_CONN_POOL *sp1 = sql_pool_create(10, "192.168.0.110", 3306, "test", "root", "950512");  
    SQL_NODE *node  = get_db_connect(sp1);  
    if (NULL == node)  
    {  
        printf("get sql pool node error.\n");  
        return -1;  
    } 
    printf("--%d-- \n", node->index);
    printf("busy--%d--\n", sp1->busy_number);
    char command[1024];
    sprintf(command,"select * from usertable where myname = '%s' and passwd = '%s';",user->name,user->passwd);
    query_mysql(&(node->fd),command);
    MYSQL_RES *result;
    result = import_result(&(node->fd));
    int ret = count_result_rows(result);
    if(ret)
    {
        ret_msg.key = 1;
    }
    else
        ret_msg.key = -1;
    write(sockfd,&ret_msg,sizeof(ret_msg));
    /*if (mysql_query(&(node->fd), "select * from usertable;"))
    {                                                    
        printf("query error.\n");                                     
        return -1;                                      
    }
    else  
    printf("succeed!\n");*/  

    sql_pool_destroy(sp1);

    return 0;  

}
