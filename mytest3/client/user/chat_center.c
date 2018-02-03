/*************************************************************************
	> File Name: chat_center.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月25日 星期四 11时05分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"user.h"
#include"chat_center.h"
void menu()
{
    printf("1.群聊\n");
    printf("2.私聊\n");
    printf("3.返回\n");
    printf("0.退出\n");
}
int chat_center(struct user *user)
{
    int fd,ret;
    int y = 0;
    while(1)
    {
        menu();
        printf("请选择:\n");
        int choose;
        scanf("%d",&choose);
        switch(choose)
        {
            case 1:
            group_center(user);
            break;
            case 2:
            p2p_center(user);
            break;
            case 3:
            y = -1;
            break;
            case 4:
            exit(0);
            default:
            break;
        }

    }

}
