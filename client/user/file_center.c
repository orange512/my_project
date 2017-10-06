/*************************************************************************
	> File Name: media_center.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月04日 星期三 16时56分45秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include"msg.h"
#include"user.h"
#include"login.h"
#include"file_center.h"
static void menu()
{
    printf("\t\t************************\n");
    printf("\t\t* 1.获取文件列表       *\n");
    printf("\t\t* 2.获取文件详细信息   *\n");
    printf("\t\t* 3.下载文件           *\n");
    printf("\t\t* 4.返回               *\n");
    printf("\t\t* 0.退出               *\n");
}
int get_list()
{
    struct msg msg;
    int fd,ret;
    int i = 1;
    char buf[1024];
    msg.cmd = 2;
    msg.key = 1;

    fd = connect_server("127.0.0.1");
    if(fd < 0)
    {
        printf("连接失败\n");
        return -1;
    }
    write(fd,&msg,sizeof(msg));
    while(1)
    {
        memset(buf,0,sizeof(buf));
        ret = read(fd,buf,sizeof(buf));
        if(ret == 0)
        {
            break;
        }
        if(strncmp(buf,"end",3) == 0)
        {
            break;
        }
        printf("\t%d->%s\n",i++,buf);
    }
    close(fd);

    return 0;
}
int down_file()
{
    struct msg msg;
    int fd,ret;
    char filename[512];
    char load[1024];
    char buf[128];
    msg.cmd = 2;
    msg.key = 3;
    int myfd;
    fd = connect_server("127.0.0.1");
    if(fd < 0)
    {
        printf("连接失败\n");
        return -1;
    }
    printf("请输入你要下载的文件名\n");
    scanf("%s",filename);
    sprintf(load,"download/%s",filename);
    myfd = open(load,O_CREAT|O_WRONLY,0777);
    memcpy(msg.val,filename,sizeof(filename));
    write(fd,&msg,sizeof(msg));
    while(1)
    {
        ret = read(fd,buf,sizeof(buf));
        if(ret < 128)
        {
            break;
        }
        write(myfd,buf,ret);
    }
    write(myfd,buf,ret);
    close(fd);
    close(myfd);
    return 0;
}
int get_detail()
{
    struct msg msg;
    int fd,ret;
    int i = 1;
    char filename[1024];
    char buf[1024];
    msg.cmd = 2;
    msg.key = 2;
    fd = connect_server("127.0.0.1");
    if(fd < 0)
    {
        printf("连接失败\n");
        return -1;
    }
    printf("请输入你要查看的文件名\n");
    scanf("%s",filename);
    memcpy(msg.val,filename,sizeof(filename));
    write(fd,&msg,sizeof(msg));
    ret = read(fd,buf,sizeof(buf));
    if(ret < 0)
        return -1;
    printf("%s\n",buf);
    close(fd);
    return 0;

}
int file_center(struct user *user)
{
    int y = 0;
    int n = 0;
    while(y == 0)
    {
        menu();
        printf("\t\t请选择:\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
            get_list();
            break;
            case 2:
            get_detail();
            break;
            case 3:
            down_file();
            break;
            case 4:
            y = -1;
            break;
            case 0:
            exit(0);
            default:
            break;
        }
    }
    return 0;
}
