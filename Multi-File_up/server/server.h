/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月16日 星期一 23时30分07秒
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
pthread_t thread[4];//线程TID
int fd_sock;
int fd_data[4];//连接的描述符
char filename[20];//文件名字
struct sockaddr_in serveraddr,clientaddr;
socklen_t clilen;
int create_sock()//创建sock描述符
{
    int ret,sockfd,connfd;
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
    return sockfd;
}
void create_Des_file()//创建目地文件
{
    char buf[1024];
    clilen = sizeof(struct sockaddr);
    int fd1 = accept(fd_sock,(struct sockaddr *)&clientaddr,&clilen);
    memset(filename,0,sizeof(filename));

    int count  = read(fd1,filename,sizeof(filename));//获取传输的文件名
    buf[count] = '\0';

    int fd2 = open(filename,O_CREAT|O_WRONLY,0766);
    if(fd2 < 0)
    {
        printf("创建目的文件名失败\n");
        return;
    }
    close(fd1);
    close(fd2);
}
void rm_part()
{
    FILE *fp = NULL;
    fp = popen("rm part*","r");
    //fp = popen("~/my_project/Multi-File_up/server/rm.sh","r");//删除分块文件
    if(fp == NULL)
    {
        printf("删除失败\n");
        return;
    }
    pclose(fp);
}
void merge()//合并发送过来的文件
{
    char name[20];
    char buf[1024];
    memset(buf,0,sizeof(buf));
    int nread;
    int fd2 = open(filename,O_WRONLY);
    if(fd2 < 0)
    {
        printf("%s文件打开失败\n",filename);
        return;
    }
    for(int i = 0 ; i < 4;i++)
    {
        sprintf(name,"part%d",i);
        int fd = open(name,O_RDONLY);
        if(fd < 0)
        {
            printf("打开%d文件失败\n",i);
            return;
        }
        nread = read(fd,buf,sizeof(buf));
        if(nread < sizeof(buf))
        {
            write(fd2,buf,nread);
            continue;
        }
        write(fd2,buf,sizeof(buf));
        memset(buf,0,sizeof(buf));
        close(fd);
    }
    write(fd2,'\0',1);
    close(fd2);
}
#endif
