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
void user_menu()
{
    printf("*****1.私聊********\n");
    printf("*****2.群聊********\n");
    printf("*****0.退出********\n");
    printf("请输入你的选择:");
}
int main()
{
    msg_t msg;
    int y = 1;
    while(y==1)
    {
        int sockfd = log_sig();
        printf("client sockfd = %d\n",sockfd);
        user_menu();
        int choose;
        scanf("%d",&choose);
        switch(choose)
        {
            case PRIVATE_CHAT:
            //private_chat(msg);
            break;
            case GROUP_CHAT:
            //group_chat(msg);
            break;
            case EXIT:
            y = -1;
            break;
        }
    }
    return 0;
}
