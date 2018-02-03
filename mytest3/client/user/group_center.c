/*************************************************************************
	> File Name: group_center.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月25日 星期四 14时31分52秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>  /* See NOTES */
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"chat_center.h"
#include"user.h"
#include"login.h"
int group_center(struct user *user)
{
    int ret,sock;
    sock = connect_server("127.0.0.1");
    if(sock < 0)
    {
        printf("connect_server failure\n");
        return -1;
    }
    fd_set rset;
    FD_ZERO(&rset);
    int y = 1;
    int nready = 0;
    int maxfd;
    int std = fileno(stdin);
    if(std > sock)
        maxfd = std;
    else
        maxfd = sock;
    while(y == 1)
    {
        FD_SET(sock,&rset);
        FD_SET(std,&rset);

        nready = select(maxfd + 1,&rset,NULL,NULL,NULL);
        if(nready < 0)
            perror("select");
        if(nready = 0)
            continue;
        if(FD_ISSET(sock,&rset))
        {
            int ret = recv(sock,recvbuff,sizeof(recvbuff),0);
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
            if(!strcmp(sendbuff,"/exit"))
            {
                y = -1;
                break;
            }
            send(sock,sendbuff,sizeof(sendbuff),0);
            memset(sendbuff,0,sizeof(sendbuff));
        }
    }
    close(sock);
    return 0;

}

