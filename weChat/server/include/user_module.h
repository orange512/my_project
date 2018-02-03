/*************************************************************************
	> File Name: user_module.h
	> Author: 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 17时40分31秒
 ************************************************************************/

#ifndef _USER_MODULE_H
#define _USER_MODULE_H

int user_module(int connfd,struct msg msg);
int login_server(int connfd,struct msg msg);

int sigin_server(int connfd,struct msg msg);
int forget_passwd(int connfd,struct msg msg);
#endif
