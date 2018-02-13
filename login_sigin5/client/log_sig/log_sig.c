/*************************************************************************
	> File Name: log_sig.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月02日 星期五 14时04分58秒
 ************************************************************************/
#include"log_sig.h"
void menu()
{
    printf("*****1.注册********\n");
    printf("*****2.登录********\n");
    printf("*****0.退出********\n");
    printf("请输入你的选择:");
}
int log_sig()
{
    msg_t msg,ret_msg;
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
            ret_msg = sigin(msg);
            if(ret_msg.key > 1)
            {
                y = -1;
                return ret_msg.key;
            }
            case LOGIN:
            msg.cmd = LOGIN;
            int sockfd = login(msg);
            if(sockfd > 1)
            {
                y = -1;
                return sockfd ;
            }
            case EXIT:
            exit(EXIT_SUCCESS);
            break;
        }
    }
}
