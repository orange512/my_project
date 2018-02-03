/*************************************************************************
	> File Name: up_file.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月06日 星期五 14时52分26秒
 ************************************************************************/

#include<stdio.h>
#include"user.h"
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include"msg.h"
#include"login.h"
int up_file(struct user *user)
{
    struct msg msg;
    int fd,ret;
    char filename[512];
    char load[1024];
    char buf[128];
    msg.cmd = 3;
    msg.key = 1;
    int myfd;
    fd = connect_server("127.0.0.1");
    if(fd < 0)
    {
        printf("连接失败\n");
        return -1;
    }
    printf("请输入你要上传的文件名\n");
    scanf("%s",filename);
    sprintf(load,"%s",filename);
    myfd = open(load,O_RDONLY);
    if(myfd < 0)
    {
        perror("open myfd");
    }
    memcpy(msg.val,load,sizeof(load));
    write(fd,&msg,sizeof(msg));
    while(1)
    {
        ret = read(myfd,buf,sizeof(buf));
        if(ret < 128)
        {
            break;
        }
        write(fd,buf,ret);
    }
    write(fd,buf,ret);
    close(fd);
    close(myfd);
    return 0;
}
