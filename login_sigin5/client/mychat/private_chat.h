/*************************************************************************
	> File Name: private_chat.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月12日 星期一 21时03分49秒
 ************************************************************************/

#ifndef _PRIVATE_CHAT_H
#define _PRIVATE_CHAT_H
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
int my_io_reuse(int sockfd,int friend_fd);
int private_chat(int sockfd,msg_t msg);
#endif
