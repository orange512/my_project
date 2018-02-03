/*************************************************************************
	> File Name: private_chat.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月03日 星期六 14时57分50秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>  /* See NOTES */
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"../include/msg.h"
int my_io_reuse(int sockfd,msg_t msg)
{
    char sendbuff[1024] = {0};
    char recvbuff[1024] = {0};
    fd_set rset;
    FD_ZERO(&rset);
    int nready = 0;
    int maxfd;
    int std = fileno(stdin);
    if(std > sockfd)
        maxfd = std;
    else
        maxfd = sockfd;
    while(1)
    {
        FD_SET(sockfd,&rset);
        FD_SET(std,&rset);

        nready = select(maxfd + 1,&rset,NULL,NULL,NULL);
        if(nready < 0)
            perror("select");
        if(nready = 0)
            continue;
        if(FD_ISSET(sockfd,&rset))
        {
            int ret = recv(sockfd,recvbuff,sizeof(recvbuff),0);
            if(ret == -1)
                perror("recv");
            if(ret == 0)
            {
                printf("server close\n");
                exit(EXIT_SUCCESS);
            }
            fputs(recvbuff,stdout);
            putchar(10);
            fflush(stdout);
            memset(recvbuff,0,sizeof(recvbuff));
        }
        if(FD_ISSET(std,&rset))
        {
           if(fgets(sendbuff,sizeof(sendbuff),stdin) == NULL)
                break;
            send(sockfd,sendbuff,sizeof(sendbuff),0);
            memset(sendbuff,0,sizeof(sendbuff));
        }
    }
    close(sockfd);
    return 0;
}

int private_chat(int sockfd,msg_t msg)
{
    
}
