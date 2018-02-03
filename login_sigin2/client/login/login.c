/*************************************************************************
	> File Name: login.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月01日 星期四 19时59分30秒
 ************************************************************************/

#include"login.h"

int LOGIN_MD5(char *passwd)
{
    int i;
    MD5_CTX md5;
    MD5Init(&md5);                          //初始化用于md5加密的结构

    unsigned char encrypt[16];     //存放于加密的信息
    unsigned char decrypt[17];       //存放加密后的结果
    scanf("%s",encrypt);                 //输入加密的字符
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
int login(msg_t msg)
{
    user_t user;
    msg_t ret_msg;
    memset(&user,0,sizeof(user_t));
    //user =(struct user *) msg->val;
    printf("请输入你的用户名\n");
    scanf("%s",user.name);
    printf("请输入你的密码(16位)\n");
    LOGIN_MD5((user.passwd));
    printf("passwd : ->%s\n",user.passwd);
    memcpy(msg.val,&user,sizeof(struct user));
    ret_msg = send_server("127.0.0.1",msg);
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
    if(ret_msg.key == 1)
    {
        printf("恭喜你登录成功\n");
    }
    return 0;
}
