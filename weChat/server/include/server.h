/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 18时24分27秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H
int handle_client(int connfd,struct msg msg);

int user_module(int connfd,struct msg msg);
int file_module(int connfd,struct msg msg);
int chat_module(int connfd,struct msg msg);
int red_module(int connfd,struct msg msg);
#endif
