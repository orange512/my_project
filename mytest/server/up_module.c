/*************************************************************************
	> File Name: up_module.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月06日 星期五 15时10分00秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include"msg.h"

int myup_file(int connfd,struct msg msg)
{
    int ret;
    char filename[1024];
    char buf[1024];
    sprintf(filename,"file/%s",msg.val);
    int fd = open(filename,O_CREAT|O_WRONLY,0777);
    if(fd < 0)
    {
        printf("打开失败\n");
        return -1;
    }
    while(1)
    {
        ret = read(connfd,buf,128);
        if(ret < 128)
        {
            break;
        }
        write(fd,buf,ret);
    }
    write(fd,buf,ret);
    close(fd);
    close(connfd);
    return 0;

}
int up_module(int connfd,struct msg msg)
{
    switch(msg.key)
    {
        case 1:
        myup_file(connfd,msg);
        break;
        case 2:
        case 3:
        break;
        default:
        break;
    }
    return 0;
}
