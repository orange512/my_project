/*************************************************************************
	> File Name: user_main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月04日 星期三 16时40分57秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"user.h"
#include"user_main.h"
static void menu()
{
    printf("\t\t************************\n");
    printf("\t\t*  1.用户管理中心      *\n");
    printf("\t\t*  2.文件查看及下载    *\n");
    printf("\t\t*  3.上传我的文件      *\n");
    printf("\t\t*  4.返回              *\n");
    printf("\t\t*  0.退出              *\n");
}
int user_main(struct user *user)
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
            //用户管理
            break;
            case 2:
            //文件查看及下载
            printf("欢迎进入文件中心\n");
            file_center(user);
            break;
            case 3:
            //上传中心
            up_file();
            break;
            case 4:
            y = -1;
            //返回
            break;
            case 0:
            //退出
            exit(0);
            break;

        }
    }
    return 0;
}
