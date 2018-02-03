/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: 2017年09月29日 星期五 20时57分12秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

int user_module(int connfd,struct msg msg);
int play_module(int connfd,struct msg msg);
int up_module(int connfd,struct msg msg);
extern MYSQL *mysql;
#endif
