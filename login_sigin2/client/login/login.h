/*************************************************************************
	> File Name: login.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月01日 星期四 20时02分34秒
 ************************************************************************/

#ifndef _LOGIN_H
#define _LOGIN_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../include/msg.h"
#include"../include/user.h"
#include"../md5/MD5.h"
#include"../tool/connect_server.h"
int LOGIN_MD5(char *passwd);
int login(msg_t msg);
#endif
