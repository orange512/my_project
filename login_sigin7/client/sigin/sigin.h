/*************************************************************************
	> File Name: sigin.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 15时38分39秒
 ************************************************************************/

#ifndef _SIGIN_H
#define _SIGIN_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../include/msg.h"
#include"../include/user.h"
#include"../md5/MD5.h"
#include"../tool/connect_server.h"
#include"../no_echo_passwd/noecho_passwd.h"
int MD5(char *passwd);
msg_t sigin(msg_t msg);
#endif
