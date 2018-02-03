/*************************************************************************
	> File Name: sigin.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 16时28分06秒
 ************************************************************************/

#include "sigin.h"
int user_identify(int sockfd,msg_t msg)
{
    user_t *user;
    //memcpy(msg.val,&user,sizeof(user_t));
    user =(user_t*)msg.val;
    printf("user->name:%s\n",user->name);
    printf("user->passwd:%s\n",user->passwd);
    msg_t ret_msg;
    SQL_CONN_POOL *sp = sql_pool_create(10, "192.168.0.110", 3306, "test", "root", "950512");  
    SQL_NODE *node  = get_db_connect(sp);  
    if (NULL == node)  
    {  
        printf("get sql pool node error.\n");  
        return -1;  
    } 
    printf("--%d-- \n", node->index);
    printf("busy--%d--\n", sp->busy_number);
    char command[1024];
    sprintf(command,"insert into usertable(myname,passwd) values('%s','%s'); ",user->name,user->passwd);
    query_mysql(&(node->fd),command);
    int ret = affected_rows(&(node->fd));
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

    //sql_pool_destroy(sp);

    return 0;  

}
int sigin(int sockfd,msg_t msg)
{
    printf("msg.cmd = %d\n",msg.cmd);
    printf("msg.key = %d\n",msg.key);
    switch(msg.key)
    {
        case 1:
        user_identify(sockfd,msg);
        break;
      /************/
    }
}
