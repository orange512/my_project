/*************************************************************************
	> File Name: group_chat.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月22日 星期四 16时37分02秒
 ************************************************************************/

#include<stdio.h>

#include"group_chat.h"
extern struct cli_info cli_info[MAX_CLI_SIZE];
extern struct group_info group_info[MAX_GROUP_SIZE];
extern SQL_CONN_POOL *sp;
char groupname[16];
struct friend_msg final_friend_msg;

/*int get_group_field(int sockfd,msg_t msg)
{
    struct group_msg group_msg;
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
    sprintf(command,"select Gname from grouptable where GID in(
        select GID from join_group where myname = '%s');",username);
    query_mysql(&(search_node->fd),command);
    MYSQL_RES *result;
    result = import_result(&(search_node->fd));
    MYSQL_ROW row = NULL;
    int field_num = mysql_field_count(&(search_node->fd));
    printf("field_num = %d\n",field_num);
    while((row = mysql_fetch_row(result)))
    {
        for(int i = 0 ; i < field_num;i++)
        {
            printf("%s",row[i]);
            sprintf(group_msg.name[i],"%s",row[i]);
        }
    }
    display_table_content(&(search_node->fd),result);
    return field_num;
}*/
int send_group_list(int sockfd,msg_t msg)
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
    sprintf(command,"select Gname from grouptable where GID in(select GID from join_group where myname = '%s');",username);
    query_mysql(&(search_node->fd),command);
    MYSQL_RES *result;
    result = import_result(&(search_node->fd));
    int count = count_result_rows(result);
    MYSQL_ROW row = NULL;
    int field_num = mysql_field_count(&(search_node->fd));
    int j = 0;
    while((row = mysql_fetch_row(result)))
    {
        for(int i = 0 ; i < field_num;i++)
        {
            printf("i = %d....%s\n",i,row[i]);
            sprintf(friend_msg.name[j++],"%s",row[i]);
        }
    }
    //display_table_content(&(search_node->fd),result);
    msg.key = count;
    memcpy(msg.val,&friend_msg,sizeof(friend_msg));
    send(sockfd,&msg,sizeof(msg_t),0);
    return 0;
}
/*int judge_groupmember_onlinee(int sockfd,msg_t msg)
{
    int i,to_fd;
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
    return to_fd;
}*/
int send_group_msg(int sockfd,msg_t msg)
{
    if(!strcmp(msg.val,"EXIT"))
    {
        msg.key = -4;//客户退出聊天
        send(msg.chat_sockfd,&msg,sizeof(msg_t),0);
    }
    else
    {
        for(int i = 0 ; i < MAX_CLI_SIZE;i++)
        {
            if(!strcmp(cli_info[i].cli_name,"'\0'") || cli_info[i].cli_sockfd < 0)
                break;
            for(int j = 0;j < 64;j++)
            {
                if(final_friend_msg.name == NULL)
                    break;
                if(!strcmp(cli_info[i].cli_name,final_friend_msg.name[j]))
                {
                    if(cli_info[i].cli_sockfd == sockfd)
                        break;
                    printf("clifd = %s\n",cli_info[i].cli_name);
                    send(cli_info[i].cli_sockfd,&msg,sizeof(msg_t),0);
                    printf("error = %s\n",strerror(errno));
                }
            }
        }
        
    }    
    return 0;

}
/*int judge_groupname()
{
    for(int i = 0;i < MAX_GROUP_SIZE;i++)
    {
        if(group_info[i].is_use == 1)
        {
            if(!strcmp(group_info[i].groupname,groupname))
                return 1;
        }
    }
    return 0;
}
int select_empty_struct()
{
    
}*/
int send_groupmember_list(int sockfd,msg_t msg)
{

    SQL_NODE *search_node = get_db_connect(sp);
    if(NULL == search_node)
    {
        printf("get sql pool node error\n");
        return -1;
    }
    printf("--%d-- \n", search_node->index);
    printf("busy--%d--\n", sp->busy_number);
    memcpy(&final_friend_msg,msg.val,sizeof(final_friend_msg));
    printf("cmd = %d \t key = %d \t val = %s\n",msg.cmd,msg.key,msg.val);
    printf("friend_msg.name = %s\n",final_friend_msg.name[0]);
    char command[1024];
    sprintf(command,"select uid from groupmember where group_id  = (select group_id from grouptable where Gname = '%s')",final_friend_msg.name[0]);
    memcpy(groupname,final_friend_msg.name[0],sizeof(final_friend_msg.name[0]));
    query_mysql(&(search_node->fd),command);
    MYSQL_RES *result;
    result = import_result(&(search_node->fd));
    int count = count_result_rows(result);
    MYSQL_ROW row = NULL;
    int field_num = mysql_field_count(&(search_node->fd));
    int j = 0;
    memset(&final_friend_msg,0,sizeof(final_friend_msg));
    while((row = mysql_fetch_row(result)))
    {
        for(int i = 0 ; i < field_num;i++)
        {
            printf("%s\n",row[i]);
            sprintf(final_friend_msg.name[j++],"%s",row[i]);
        }
    }
    //display_table_content(&(search_node->fd),result);
    msg.key = count;
    memcpy(msg.val,&final_friend_msg,sizeof(final_friend_msg));
    send(sockfd,&msg,sizeof(msg_t),0);
    release_node(sp,search_node);
    return 0;


}
int group_chat(int sockfd,msg_t msg)
{
    switch(msg.key)
    {
        case 1:
        //获取群列表
        send_group_list(sockfd,msg);
        break;
        case 2:
        send_groupmember_list(sockfd,msg);
        break;
        case 3:
        //判断群成员是否在线
        //judge_groupmember_online(sockfd,msg);
        break;
        case 4:
        send_group_msg(sockfd,msg);
        break;
    }
    return 0;
}
