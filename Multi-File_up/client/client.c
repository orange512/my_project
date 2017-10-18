/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月16日 星期一 20时15分26秒
 ************************************************************************/

#include<stdio.h>
#include"client.h"
static char Filename[50];
static char Load[512];
static char myfile[1024];
void *thread_send_data(void *arg)//线程发送分块数据
{
    int index = *(int *)arg;
    char buf[1024];
    int conn;
    conn = connect_server("127.0.0.1");
    int fd_file = open(myfile,O_RDONLY);
    if(fd_file < 0)
    {
        printf("fd_file error\n");
        return NULL;
    }
    lseek(fd_file,block[index].offset,SEEK_SET);//偏移指针到读取位置
    int count = block[index].size;
    write(conn,&index,4);//发送文件编号给服务器
    int min = count;
    if(min > sizeof(buf))
        min = sizeof(buf);

    while(count > 0)
    {
        int count_read = read(fd_file,buf,min);
        write(conn,buf,count_read);
        count = count - count_read;
    }
    close(fd_file);
    close(conn);
}
void Get_Filename()
{
    printf("请输入你要上传的文件路径\n");
    scanf("%s",Load);
    printf("请输入你的文件名\n");
    scanf("%s",Filename);
    sprintf(myfile,"%s/%s",Load,Filename);

}
int main(int argc,char *argv[])
{
    int fd_file;
    int total;
    int arg[4];
    fd_sock = connect_server("127.0.0.1");
    Get_Filename();
    if((fd_file = open(myfile,O_RDONLY)) < 0)
    {
        printf("找不到你上传的文件，请重新上传\n");
        return -1;
    }

    write(fd_sock,Filename,strlen(Filename));//向服务器发送要发送的文件名
    close(fd_sock);

    total = lseek(fd_file,0,SEEK_END);//获取文件大小
    int count_per = (int)(total / 4);//发送块的平均大小
    for(int i = 0 ; i < 4; i++)
    {
        block[i].offset = i * count_per;
        block[i].size = count_per;
        if(i == 3)
            block[i].size = total - i * count_per;
    }
    //创建子线程
    for(int i = 0 ; i < 4 ;i++)
    {
        arg[i] = i;
        pthread_create(&thread[i],NULL,thread_send_data,(void *)&arg[i]);
    }
    for(int i = 0 ; i < 4;i++)
    {
        pthread_join(thread[i],NULL);
    }
    printf("上传文件%s成功\n",Filename);

    return 0;
}

