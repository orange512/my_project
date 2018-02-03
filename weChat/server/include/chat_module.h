/*************************************************************************
	> File Name: chat_module.h
	> Author: 
	> Mail: 
	> Created Time: 2017年11月03日 星期五 18时31分24秒
 ************************************************************************/

#ifndef _CHAT_MODULE_H
#define _CHAT_MODULE_H
int group_chat(int connfd,struct msg msg);
int private_chat(int connfd,struct msg msg);
#endif
