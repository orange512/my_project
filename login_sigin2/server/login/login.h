/*************************************************************************
	> File Name: login.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月31日 星期三 10时26分13秒
 ************************************************************************/

#ifndef _LOGIN_H
#define _LOGIN_H
#include<stdio.h>
#include<unistd.h>
#include"../include/msg.h"
#include"../include/user.h"
#include"../API_MYSQL/api_mysql.h"
#include"../SQL_POLL/sql_pool.h"
int login(int sockfd,msg_t msg);
#endif
