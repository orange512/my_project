/*************************************************************************
	> File Name: private_chat.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月03日 星期六 14时57分50秒
 ************************************************************************/
#include"private_chat.h"
#include<errno.h>

extern char username[16];
char friend_name[16];
int my_io_reuse(int sockfd,int friend_fd)
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
                printf("对方退出了私聊\n");
                return sockfd;
            }
            printf("%s:",friend_name);
            fputs(recv_msg.val,stdout);
            putchar(10);
            fflush(stdout);
            memset(&recv_msg,0,sizeof(recv_msg));
        }
        if(FD_ISSET(std,&rset))
        {
           if(fgets(send_msg.val,sizeof(send_msg),stdin) == NULL)
                break;
            send_msg.cmd = 3;
            send_msg.key = 3;//私聊发送消息
            send_msg.chat_sockfd = friend_fd;
            send(sockfd,&send_msg,sizeof(send_msg),0);
            if(!strncmp(send_msg.val,"EXIT",4))
            {
                return sockfd;
            }
            memset(&send_msg,0,sizeof(send_msg));
        }
    }
    return 0;
}

int private_chat(int sockfd,msg_t msg)
{
    printf("sockfd = %d\n",sockfd);
    printf("正在获取好友列表:...\n");
    msg_t ret_msg;
    msg.key = 1;//获取好友列表
    printf("username= %s\n",username);
    memcpy(msg.val,username,sizeof(&username));
    send(sockfd,&msg,sizeof(msg_t),0);
    printf("error = %s\n",strerror(errno));
    recv(sockfd,&ret_msg,sizeof(msg_t),0);
    printf("error = %s\n",strerror(errno));
    printf("ret_msg.cmd = %d\n",ret_msg.cmd);
    struct friend_msg send_friend;
    memcpy(&send_friend,ret_msg.val,sizeof(msg.val));
    printf("以下是你的好友列表\n");
    for(int i = 0 ; i  < ret_msg.key;i++)
    {
        printf("\t\t%d:%s\n",i+1,send_friend.name[i]);
    }
    printf("请选择好友(输入编号)\n");
    int choose;
    scanf("%d",&choose);
    memset(msg.val,0,sizeof(msg.val));
    memset(&ret_msg,0,sizeof(msg_t));

    msg.cmd = 3;
    msg.key = 2;//判断好友是否在线
    printf("name = %s\n",send_friend.name[choose -1]);
    memcpy(msg.val,send_friend.name[choose-1],sizeof(send_friend.name[choose-1]));
    memcpy(friend_name,send_friend.name[choose-1],sizeof(send_friend.name[choose-1]));
    send(sockfd,&msg,sizeof(msg_t),0);
    printf("error = %s\n",strerror(errno));
    recv(sockfd,&ret_msg,sizeof(msg_t),0);
    printf("error = %s\n",strerror(errno));
    if(ret_msg.key == -1)
    {
        printf("对不起你的好友没在线\n");
        return 0;
    }
    else
    {
        printf("欢迎进入聊天室\n");
        printf("对方的ｆｄ　＝　%d\n",ret_msg.chat_sockfd);
        my_io_reuse(sockfd,ret_msg.chat_sockfd);
    }
    return 0;
}
