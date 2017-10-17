/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月16日 星期一 20时22分42秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H
#include<stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#define ERR_EXIT(m)\
        do{\
            perror(m),exit(EXIT_FAILURE);\
        }while(0)
struct block_info
{
    unsigned int size;//块的大小(字节数)
    unsigned int offset;//块在文件中的偏移量
};
pthread_t thread[4];
struct sockaddr_in serveraddr;
struct block_info block[4];
int fd_sock;
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
#endif
