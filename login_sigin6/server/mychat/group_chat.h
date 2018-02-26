/*************************************************************************
	> File Name: group_chat.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月22日 星期四 20时20分22秒
 ************************************************************************/

#ifndef _GROUP_CHAT_H
#define _GROUP_CHAT_H
#include<stdio.h>
#include"../include/msg.h"
#include"../server.h"
#include"../include/friend_msg.h"
#include"../include/group_info.h"
#include"../include/group_msg.h"
int send_group_list(int sockfd,msg_t msg);
int send_groupmember_list(int sockfd,msg_t msg);
//int judge_groupmember_online(int sockfd,msg_t msg);
int send_group_msg(int sockfd,msg_t msg);
int group_chat(int sockfd,msg_t msg);
#endif
