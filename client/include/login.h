/*************************************************************************
	> File Name: login.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月03日 星期二 18时01分10秒
 ************************************************************************/

#ifndef _LOGIN_H
#define _LOGIN_H
struct user login_main();
struct msg send_server(char *ip,struct msg msg);
int  connect_server(char *ip);
int client_sigin(struct user *user);
int client_login(struct user *user);
#endif
