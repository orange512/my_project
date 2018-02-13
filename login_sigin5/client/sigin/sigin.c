/*************************************************************************
	> File Name: sigin.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月30日 星期二 14时59分03秒
 ************************************************************************/

#include"sigin.h"
int MD5(char *passwd)
{
    int i;
    MD5_CTX md5;
    MD5Init(&md5);                          //初始化用于md5加密的结构

    unsigned char encrypt[16];     //存放于加密的信息
    unsigned char decrypt[17];       //存放加密后的结果
    
    set_disp_mode(STDIN_FILENO,0);
    scanf("%s",encrypt);                 //输入加密的字符
    set_disp_mode(STDIN_FILENO,1);
    char temp[2];
    MD5Update(&md5,encrypt,strlen((char *)encrypt));   //对欲加密的字符进行加密
    MD5Final(decrypt,&md5);                                             //获得最终结果

    printf("加密前:%s\n加密后:",encrypt);
    for(i=0; i<16; i++)
    {
        printf("%02x",decrypt[i]);
        sprintf(temp,"%02x",decrypt[i]);
        strcat(passwd,temp);
    }
    printf("\n\n\n加密结束!\n");
    return 0;

}
msg_t sigin(msg_t msg)
{
    user_t user;
    msg_t ret_msg;
    memset(&user,0,sizeof(user_t));
    //user =(struct user *) msg->val;
    printf("请输入你的用户名\n");
    scanf("%s",user.name);
    printf("请输入你的密码(16位)\n");
    MD5(user.passwd);
    msg.key = 1;
    printf("passwd : ->%s",user.passwd);
    memcpy(msg.val,&user,sizeof(struct user));
    //ret_msg = send_server("127.0.0.1",msg);
    int sockfd = connect_server("127.0.0.1");
    write(sockfd,&msg,sizeof(msg));
    read(sockfd,&ret_msg,sizeof(ret_msg));
    
    printf("链接成功.........\n");
    if(ret_msg.key == -1)
    {
        printf("您输入的用户名已经存在\n");
        return ret_msg;
    }
    if(ret_msg.key == -2)
    {
        printf("您输入的信息有误\n");
        return ret_msg;
    }
    if(ret_msg.key > 1)
    {
        printf("恭喜你登录成功\n");
    }
    return ret_msg;
}
