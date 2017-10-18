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
    {
        printf("创建分块文件%d失败\n",index);
        return NULL;
    }
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
    fd_sock = create_sock();
    int arg[4];
    create_Des_file();//接受客户端的文件名，并在服务器创建目标文件
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
    rm_part();//删除分块文件

    return 0;

}
