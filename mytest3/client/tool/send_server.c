/*************************************************************************
	> File Name: send_connet.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月03日 星期二 17时07分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"msg.h"
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(EXIT_FAILURE);\
        }while(0)
int connect_server(char *ip)
{
    int sockfd ,ret;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        ERR_EXIT("socket");
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(51990);
    inet_aton(ip,&serveraddr.sin_addr);
    if((ret = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))) < 0)
    { 
        ERR_EXIT("connect");
    }
    return sockfd;

}
struct msg send_server(char *ip,struct msg msg)
{
    int sockfd ,ret;
    struct msg ret_msg;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        ERR_EXIT("socket");
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(51990);
    inet_aton(ip,&serveraddr.sin_addr);
    if((ret = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))) < 0)
    {
        ret_msg.key = -2; 
        ERR_EXIT("connect");
    }
    write(sockfd,&msg,sizeof(msg));
    read(sockfd,&ret_msg,sizeof(ret_msg));
    close(sockfd);
    return ret_msg;
}
