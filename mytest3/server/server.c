/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月29日 星期五 16时53分50秒
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<mysql/mysql.h>
#include"api_mysql.h"
#include"msg.h"
#include"server.h"
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(EXIT_FAILURE);\
        }while(0)
int handle_client(int connfd)
{
    struct msg msg;
    read(connfd,&msg,sizeof(msg));
    printf("msg.cmd = %d,msg.key = %d\n",msg.cmd,msg.key);
    switch(msg.cmd)
    {
        case USER_MODULE:
        user_module(connfd,msg);
        break;
        case PLAY_MODULE:
        play_module(connfd,msg);
        break;
        case UP_MODULE:
        up_module(connfd,msg);
        break;
        case CHAT_MODULE:
        chat_module(connfd,msg);
        default:
        break;
    }
    return 0;
}
int main()
{
    MYSQL *mysql;
    mysql = finished_mysql();
    int ret,sockfd,connfd;
    pid_t pid;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t clilen = sizeof(clilen);
    memset(&clilen,0,sizeof(clilen));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(51990);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //socket
    if( (sockfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
        ERR_EXIT("socket");
    //bind
    int on = 1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))< 0)//地址重复利用
        ERR_EXIT("setsockopt");
    if((ret = bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr)))< 0)
        ERR_EXIT("bind");
    //listen
    if((ret = listen(sockfd,SOMAXCONN))< 0)
        ERR_EXIT("listen");
    //accept
    while(1)
    {
        connfd = accept(sockfd,(struct sockaddr*)&clientaddr,&clilen);

        pid = fork();
        if(pid == 0)
        {
            close(sockfd);
            handle_client(connfd);
            close(connfd);
            exit(0);
        }
    }
}
