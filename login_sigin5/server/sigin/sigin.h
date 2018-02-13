/*************************************************************************
	> File Name: sigin.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 17时11分09秒
 ************************************************************************/

#ifndef _SIGIN_H
#define _SIGIN_H
#include<stdio.h>
#include<unistd.h>
#include"../include/msg.h"
#include"../include/user.h"
#include"../API_MYSQL/api_mysql.h"
#include"../SQL_POLL/sql_pool.h"
#include"../server.h"
int user_identify(int sockfd,msg_t msg);
int sigin(int sockfd,msg_t msg);
#endif
