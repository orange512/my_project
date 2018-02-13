/*************************************************************************
	> File Name: api_epoll.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月27日 星期六 16时54分26秒
 ************************************************************************/

#ifndef _API_EPOLL_H
#define _API_EPOLL_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <pthread.h>
#include"../sigin/sigin.h"
#include"../login/login.h"
#include"msg.h"
#include"user.h"
#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 1024
typedef struct fds
{
   int epollfd;
   int sockfd;
}fds;

int setnonblocking( int fd );
void addfd( int epollfd, int fd, int oneshot );
void reset_oneshot( int epollfd, int fd );
void* worker( void* arg );
void* mytask( void* arg );
#endif
