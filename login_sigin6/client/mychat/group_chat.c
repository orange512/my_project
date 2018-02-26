/*************************************************************************
	> File Name: group_chat.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月14日 星期三 10时43分36秒
 ************************************************************************/

#include<stdio.h>

#include"group_chat.h"
#include"../include/group_msg.h"
#include<errno.h>

extern char username[16];
char groupname[16];
//char friend_name[16];
int my_io_group(int sockfd,int choose)
{
    msg_t send_msg,recv_msg;
    memset(&send_msg,0,sizeof(send_msg));
    memset(&recv_msg,0,sizeof(recv_msg));
    fd_set rset;
    FD_ZERO(&rset);
    int nready = 0;
    int maxfd;
    int std = fileno(stdin);
    if(std > sockfd)
        maxfd = std;
    else
        maxfd = sockfd;
    while(1)
    {
        FD_SET(sockfd,&rset);
        FD_SET(std,&rset);

        nready = select(maxfd + 1,&rset,NULL,NULL,NULL);
        if(nready < 0)
            perror("select");
        if(nready == 0)
            continue;
        if(FD_ISSET(sockfd,&rset))
        {
            int ret = recv(sockfd,&recv_msg,sizeof(recv_msg),0);
            if(ret == -1)
                perror("recv");
            if(ret == 0)
            {
                printf("server close\n");
                exit(EXIT_SUCCESS);
            }
            if(recv_msg.key == -4)
            {
                return sockfd;
            }
            fputs(recv_msg.val,stdout);
            putchar(10);
            fflush(stdout);
            memset(&recv_msg,0,sizeof(recv_msg));
        }
        if(FD_ISSET(std,&rset))
        {
           if(fgets(send_msg.val,sizeof(send_msg),stdin) == NULL)
                break;
            send_msg.cmd = 4;
            send_msg.key = 4;//群聊发送消息
            send_msg.chat_sockfd = choose;
            send(sockfd,&send_msg,sizeof(send_msg),0);
            memset(&send_msg,0,sizeof(send_msg));
        }
    }
    return 0;
}

int display_groupmember_list(int sockfd,msg_t msg,struct friend_msg friend_msg)
{
    msg_t ret_msg;
    printf("请选择好友(输入编号)\n");
    int choose;
    scanf("%d",&choose);
    memset(msg.val,0,sizeof(msg.val));
    memset(&ret_msg,0,sizeof(msg_t));
    msg.cmd = 4;
    msg.key = 2;//查询群列表
    printf("name = %s\n",friend_msg.name[choose -1]);
    memcpy(msg.val,friend_msg.name[choose-1],sizeof(friend_msg.name[choose-1]));
    printf("%s的列表人\n",friend_msg.name[0]);
    memcpy(groupname,friend_msg.name[0],sizeof(friend_msg.name[0]));
    send(sockfd,&msg,sizeof(msg_t),0);
    printf("error = %s\n",strerror(errno));
    memset(&friend_msg,0,sizeof(friend_msg));
    recv(sockfd,&ret_msg,sizeof(msg_t),0);
    memcpy(&friend_msg,ret_msg.val,sizeof(msg.val));
    printf("error = %s\n",strerror(errno));
    for(int i = 0 ; i  < ret_msg.key;i++)
    {
        printf("\t\t%d:%s\n",i+1,friend_msg.name[i]);
    }
    printf("欢迎进入群聊天室\n");
    my_io_group(sockfd,choose);
    return 0;
}
int group_chat(int sockfd,msg_t msg)
{
    printf("sockfd = %d\n",sockfd);
    printf("正在获取群列表:...\n");
    msg_t ret_msg;
    msg.key = 1;//获取群列表
    printf("username= %s\n",username);
    memcpy(msg.val,username,sizeof(&username));
    send(sockfd,&msg,sizeof(msg_t),0);
    printf("error = %s\n",strerror(errno));
    recv(sockfd,&ret_msg,sizeof(msg_t),0);
    printf("error = %s\n",strerror(errno));
    printf("ret_msg.cmd = %d\n",ret_msg.cmd);
    struct friend_msg friend_msg;
    memcpy(&friend_msg,ret_msg.val,sizeof(msg.val));
    printf("以下是你的群列表\n");
    for(int i = 0 ; i  < ret_msg.key;i++)
    {
        printf("\t\t%d:%s\n",i+1,friend_msg.name[i]);
    }
    //memset(&friend_msg,0,sizeof(friend_msg));
    display_groupmember_list(sockfd,msg,friend_msg);
    return 0;

}
