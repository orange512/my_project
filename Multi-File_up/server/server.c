/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月16日 星期一 21时01分19秒
 ************************************************************************/
#include<stdio.h>
#include"server.h"

void *thread_recv_data(void *arg)//线程接受传输分块文件
{
    int index = *(int*)arg;
    int temp;
    char buf[1024];
    char file[20];
    read(fd_data[index],&temp,sizeof(temp));//获取文件编号
    sprintf(file,"part%d",temp);
    int fd_file = open(file,O_WRONLY|O_CREAT,0766);//创建分块文件
    if(fd_file < 0)
        ERR_EXIT("thread open\n");
    while(1)
    {
        int count = read(fd_data[index],buf,sizeof(buf));
        if(count == 0)
            break;
        //printf("thread:%d\n",count);
        write(fd_file,buf,count);
    }
    close(fd_data[index]);
    close(fd_file);
}
int main()
{
    int i = 0 ;
    int fd_sock = create_sock();
    char buf[1024];
    int arg[4];

    clilen = sizeof(struct sockaddr);
    int fd1 = accept(fd_sock,(struct sockaddr *)&clientaddr,&clilen);
    memset(filename,0,sizeof(filename));

    int count  = read(fd1,filename,sizeof(filename));//获取传输的文件名
    buf[count] = '\0';

    int fd2 = open(filename,O_CREAT|O_WRONLY,0766);
    if(fd2 < 0)
        ERR_EXIT("open");
    close(fd1);
    close(fd2);
    while(1)
    {
        clilen = sizeof(struct sockaddr);
        fd_data[i] = accept(fd_sock,(struct sockaddr *)&clientaddr,&clilen);
        arg[i] = i;//解决传参覆盖
        pthread_create(&thread[i],NULL,thread_recv_data,(void*)&arg[i]);
        i++;
        if(i == 4)
            break;
    }
    for(i = 0 ; i < 4;i++)
    {
        pthread_join(thread[i],NULL);
    }

    merge();//合并分块文件
    printf("接受到的文件%s成功\n",filename);
    popen("~/my_project/Multi-File_up/server/rm.sh","r");//删除分块文件

    return 0;

}
