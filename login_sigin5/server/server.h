/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月01日 星期四 20时34分49秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H
#include<stdio.h>

#include <sys/types.h>      
#include <sys/socket.h>
#include <unistd.h>
#include<stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include<sys/epoll.h>
#include"./include/api_epoll.h"
#include"./include/thread_pool.h"
#include"./SQL_POLL/sql_pool.h"
#include"./include/cli_info.h"

#define ERR_EXIT(m)\
        do{\
            perror(m),\
            exit(EXIT_FAILURE);\
        }while(0)
int create_sock();
int my_epoll(int listenfd);
int server_start();
#endif
