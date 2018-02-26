/*************************************************************************
	> File Name: connect_server.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 14时42分47秒
 ************************************************************************/
#include"connect_server.h"
int connect_server(char *ip)
{
    int sockfd ,ret;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        ERR_EXIT("socket");
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9000);
    inet_aton(ip,&serveraddr.sin_addr);
    if((ret = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))) < 0)
    { 
        ERR_EXIT("connect");
    }
    printf("success ........\n");
    return sockfd;

}
msg_t send_server(char *ip,msg_t msg)
{
    printf("diaoyogn  .... \n");
    int sockfd ,ret;
    msg_t ret_msg;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        ERR_EXIT("socket");
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9000);
    inet_aton(ip,&serveraddr.sin_addr);
    if((ret = connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))) < 0)
    {
        ret_msg.key = -2; 
        ERR_EXIT("connect");
    }
    printf("link  OK......\n");
    write(sockfd,&msg,sizeof(msg));
    printf("write OK.....\n");
    read(sockfd,&ret_msg,sizeof(ret_msg));
    printf("read  OK......\n");
    close(sockfd);
    return ret_msg;
}
