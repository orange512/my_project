/*************************************************************************
	> File Name: group_chat.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月22日 星期四 20时37分06秒
 ************************************************************************/

#ifndef _GROUP_CHAT_H
#define _GROUP_CHAT_H
#include<stdio.h>
#include<string.h>
#include<sys/types.h>  /* See NOTES */
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"../login/login.h"
#include"../include/msg.h"
#include"../include/friend_msg.h"
int my_io_group(int sockfd,int choose);
int group_chat(int sockfd,msg_t msg);
int display_groupmember_list(int sockfd,msg_t msg,struct friend_msg friend_msg);
#endif
