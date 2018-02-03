/*************************************************************************
	> File Name: play_module.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月04日 星期三 20时40分49秒
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>
#include<fcntl.h>
#include"msg.h"
int get_list(int connfd)
{
    //读取文件夹
    DIR *dir = NULL;
    char buf[1024];
    dir = opendir("file/");
    if(dir == NULL)
    {
        perror("opendir");
        return -1;
    }
    while(1)
    {
        struct dirent *d = readdir(dir);
        if(d == NULL)
        {
            write(connfd,"end",3);
            break;
        }
        sprintf(buf,"%s",d->d_name);
        write(connfd,buf,sizeof(buf));
    }
    closedir(dir);
    close(connfd);
    return 0;

}
int get_detail(int connfd, struct msg msg)
{
    int ret;
    char filename[1024];
    char buf[1024];
    struct stat st = {};
    sprintf(filename,"file/%s",msg.val);
    ret = stat(filename,&st);//文件状态放入st
    if(ret == -1)
    {
        perror("stat");
        return -1;
    }
    sprintf(buf,"Inode:%ld  mode:%o  size:%ld  time:%s",st.st_ino,st.st_mode&07777,st.st_size,ctime(&st.st_mtime));
    write(connfd,buf,sizeof(buf));
    return 0;
}
int down_file(int connfd,struct msg msg)
{
    int ret;
    char filename[1024];
    char buf[128];
    sprintf(filename,"file/%s",msg.val);
    int fd = open(filename,O_RDONLY);
    if(fd < 0)
    {
        printf("打开失败\n");
        return -1;
    }
    while(1)
    {
        ret = read(fd,buf,128);
        if(ret < 128)
        {
            break;
        }
        write(connfd,buf,ret);
    }
    write(connfd,buf,ret);
    close(fd);
    return 0;
}
int play_module(int connfd,struct msg msg)
{
    switch(msg.key)
    {
        case 1:
        get_list(connfd);
        break;
        case 2:
        get_detail(connfd,msg);
        case 3:
        down_file(connfd,msg);
        break;
        default:
        break;
    }
    return 0;
}
