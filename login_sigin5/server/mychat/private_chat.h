/*************************************************************************
	> File Name: private_chat.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月12日 星期一 21时08分19秒
 ************************************************************************/

#ifndef _PRIVATE_CHAT_H
#define _PRIVATE_CHAT_H
#include<stdio.h>
#include"../include/msg.h"
#include"../server.h"
#include"../include/cli_info.h"
#include"../include/friend_msg.h"
int send_friend_list(int sockfd,msg_t msg);
int private_chat(int sockfd,msg_t msg);
#endif
