/*************************************************************************
	> File Name: login.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月01日 星期四 19时59分30秒
 ************************************************************************/

#include"login.h"
extern int MD5(char *passwd);
char username[16];
int login(msg_t msg)
{
    user_t user;
    msg_t ret_msg;
    memset(&user,0,sizeof(user_t));
    memset(&ret_msg,0,sizeof(msg_t));
    printf("请输入你的用户名\n");
    scanf("%s",user.name);
    memcpy(username,user.name,sizeof(user.name));
    printf("请输入你的密码(16位)\n");
    MD5(user.passwd);
    printf("passwd : ->%s\n",user.passwd);
    memcpy(msg.val,&user,sizeof(struct user));
//    ret_msg = send_server("127.0.0.1",msg);
    int sockfd = connect_server("127.0.0.1");
    write(sockfd,&msg,sizeof(msg));
    read(sockfd,&ret_msg,sizeof(ret_msg));
    if(ret_msg.key == -1)
    {
        printf("用户名或密码错误\n");
        return -1;
    }
    if(ret_msg.key == -2)
    {
        printf("您输入的信息有误\n");
        return -1;
    }
    if(ret_msg.key > 1)
    {
        printf("恭喜你登录成功\n");
    }
    return sockfd;
}
