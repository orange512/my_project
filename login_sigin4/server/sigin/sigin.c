/*************************************************************************
	> File Name: sigin.c
	> Author: 
	> Created Time: 2018年01月30日 星期二 16时28分06秒
 ************************************************************************/

#include "sigin.h"
extern SQL_CONN_POOL *sp;
int user_identify(int sockfd,msg_t msg)
{
    user_t *user;
    user =(user_t*)msg.val;
    printf("user->name:%s\n",user->name);
    printf("user->passwd:%s\n",user->passwd);
    msg_t ret_msg;
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
        ret_msg.key = sockfd;
    }
    else
        ret_msg.key = -1;
    write(sockfd,&ret_msg,sizeof(ret_msg));
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
    return 0;
}
