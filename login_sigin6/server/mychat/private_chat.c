/*************************************************************************
	> File Name: private_chat.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月12日 星期一 20时01分58秒
 ************************************************************************/

#include"private_chat.h"
extern struct cli_info cli_info[MAX_CLI_SIZE];
extern SQL_CONN_POOL *sp;

int send_friend_list(int sockfd,msg_t msg)
{
    struct friend_msg friend_msg;
    SQL_NODE *search_node = get_db_connect(sp);
    if(NULL == search_node)
    {
        printf("get sql pool node error\n");
        return -1;
    }
    printf("--%d-- \n", search_node->index);
    printf("busy--%d--\n", sp->busy_number);
    char username[16];
    memcpy(username,msg.val,sizeof(msg.val));
    char command[1024];
    sprintf(command,"select FID from Friend  where UID = '%s';",username);
    query_mysql(&(search_node->fd),command);
    MYSQL_RES *result;
    result = import_result(&(search_node->fd));
    MYSQL_ROW row = NULL;
    int count = count_result_rows(result);
    int field_num = mysql_field_count(&(search_node->fd));
    printf("field_num = %d\n",field_num);
    int j = 0;
    while((row = mysql_fetch_row(result)))
    {
        for(int i = 0 ; i < field_num;i++)
        {
            printf("%s",row[i]);
            sprintf(friend_msg.name[j++],"%s",row[i]);
        }
    }
    display_table_content(&(search_node->fd),result);
    msg.key = count;
    memcpy(msg.val,&friend_msg,sizeof(friend_msg));
    send(sockfd,&msg,sizeof(msg_t),0);
    release_node(sp,search_node);
    return 0;
}
int judge_online(int sockfd,msg_t msg)
{
    int i;
    msg_t ret_msg;
    struct friend_msg *friend_msg;
    friend_msg = (struct friend_msg*)msg.val;
    printf("cmd = %d \t key = %d \t val = %s\n",msg.cmd,msg.key,msg.val);
    printf("friend_msg.name = %s\n",friend_msg->name[0]);
    for(i = 0 ; i < MAX_CLI_SIZE;i++)
    {
        if(!strcmp(friend_msg->name[0],cli_info[i].cli_name))
        {
            printf("cli_info = %s\n",cli_info[i].cli_name);
            if(cli_info[i].cli_sockfd > 0)
            {
                ret_msg.chat_sockfd = cli_info[i].cli_sockfd;
                printf("fd = %d\n",ret_msg.chat_sockfd);
                ret_msg.key = 1;
                send(sockfd,&ret_msg,sizeof(msg_t),0);
                break;
            }
        }
    }
    if(i == MAX_CLI_SIZE)
    {
        printf("没找到\n");
        ret_msg.key = -1;
        send(sockfd,&ret_msg,sizeof(msg_t),0);
    }
    return 0;
}
int send_chat_msg(int sockfd,msg_t msg)
{
    if(!strcmp(msg.val,"EXIT"))
    {
        msg.key = -4;//客户退出聊天
        send(msg.chat_sockfd,&msg,sizeof(msg_t),0);
    }
    else
    {
        printf("正在发送fd = %d\n",msg.chat_sockfd);
        send(msg.chat_sockfd,&msg,sizeof(msg_t),0);
        printf("error = %s\n",strerror(errno));
        
    }    
    return 0;
        

}
int private_chat(int sockfd,msg_t msg)
{
    switch(msg.key)
    {
        case 1:
        //获取好友列表
        send_friend_list(sockfd,msg);
        break;
        case 2:
        //判断好友是否在线
        judge_online(sockfd,msg);
        break;
        case 3:
        send_chat_msg(sockfd,msg);
        break;
    }
    return 0;
}
