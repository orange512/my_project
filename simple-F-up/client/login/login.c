/*************************************************************************
	> File Name: login_main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月03日 星期二 16时44分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"msg.h"
#include"login.h"
#include"user.h"
static void menu()//静态在本函数返回
{
    printf("\t\t********************************\n");
    printf("\t\t***          1. 登录        ****\n");
    printf("\t\t***          2. 注册        ****\n");
    printf("\t\t***          3.忘记密码      ***\n");
    printf("\t\t***          4.下载         ****\n");
    printf("\t\t***          5.退出         ****\n");
    printf("\t\t********************************\n");
}
int client_sigin(struct user *user)
{
    struct msg msg;
    struct msg ret_msg;
    printf("请选择类型：[1.普通用户 2.超级用户]\n");
    scanf("%d",&user->type);
    printf("请输入用户名:\n");
    scanf("%s",user->name);
    printf("请输入密码:\n");
    scanf("%s",user->passwd);
    user->flag = 1;
    msg.cmd = 1;
    msg.key = 2;
    memcpy(msg.val,user,sizeof(struct user));
    ret_msg = send_server("127.0.0.1",msg);
    if(ret_msg.key == 1)
    {
        printf("恭喜你,注册成功\n");
    }
    else
    {
        printf("注册失败，请重新注册\n");
    }
    return 0;
}
int client_login(struct user *user)
{
    struct msg msg;
    struct msg ret_msg;
    printf("请输入用户名:\n");
    scanf("%s",user->name);
    printf("请输入密码:\n");
    scanf("%s",user->passwd);

    msg.cmd = 1;
    msg.key = 1;
    memcpy(msg.val,user,sizeof(struct user));
    ret_msg = send_server("127.0.0.1",msg);
    if(ret_msg.key == 1)
    {
        printf("登录成功\n");
    }
    else if(ret_msg.key == -2)
    {
        printf("用户名不存在，请重新输入\n");
        return -1;
    }
    else if (ret_msg.key == -3)
    {
        printf("密码错误，请重新输入\n");
        return -1;
    }
    else if (ret_msg.key == -4)
    {
        printf("帐号被禁止，请联系管理员\n");
        return -1;
    }
    return 0;
}
struct user login_main()
{
    int y = 1;
    int n,ret;
    struct user user;
    while(y == 1)
    {
        menu();
        printf("请输入选择\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
            //登录
            ret = client_login(&user);
            if(ret == 0)
            {
                y = 2;
            }
            break;
            case 2:
            //注册
            ret = client_sigin(&user);
            if(ret == 0)
            {
                y = 2;
            }
            break;
            case 3:
            //忘记密码
            break;
            case 0:
            y = 0;
            break;
            default:
            break;
        }
    }
    return user;
    
}
