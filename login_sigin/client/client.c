/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 14时45分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"./include/msg.h"
#include"./tool/connect_server.h"
#include"./sigin/sigin.h"
void menu()
{
    printf("*****1.注册********\n");
    printf("*****2.登录********\n");
    printf("*****3.退出********\n");
    printf("请输入你的选择:");
}
int main()
{
    msg_t msg;
    int y = 1;
    while(y == 1)
    {
        menu();
        int choose;
        scanf("%d",&choose);
        switch(choose)
        {
            case SIGIN:
            msg.cmd = SIGIN;
            sigin(msg);
            break;
            case LOGIN:
            msg.cmd = LOGIN;
    //        login(sockfd,msg);
            break;
            case EXIT:
            y = -1;
            break;
        }

    }
    return 0;
    

}
