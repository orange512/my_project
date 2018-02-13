/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 14时45分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"./include/msg.h"
#include"./log_sig/log_sig.h"
#include"./mychat/private_chat.h"
#include"./login/login.h"
void user_menu()
{
    printf("*****1.私聊********\n");
    printf("*****2.群聊********\n");
    printf("*****0.退出********\n");
    printf("请输入你的选择:");
}
int main()
{
    while(1)
    {
        msg_t msg;
        int sockfd = log_sig();
        int y = 1;
        while(y == 1)
        {
            printf("client sockfd = %d\n",sockfd);
            user_menu();
            int choose;
            scanf("%d",&choose);
            switch(choose)
            {
                printf("你的选择为%d\n",choose);
                case 1:
                msg.cmd = 3;
                private_chat(sockfd,msg);
                break;
                case 2:
                //group_chat(msg);
                break;
                case EXIT:
                {
                   close(sockfd); 
                   y = -1;
                }
                break;
            }
        }

    }
    return 0;
}
