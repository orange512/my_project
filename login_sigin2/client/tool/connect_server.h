/*************************************************************************
	> File Name: connect_server.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 14时44分28秒
 ************************************************************************/

#ifndef _CONNECT_SERVER_H
#define _CONNECT_SERVER_H
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"../include/msg.h"
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(EXIT_FAILURE);\
        }while(0)
int connect_server(char *ip);
msg_t send_server(char *ip,msg_t msg);
#endif
