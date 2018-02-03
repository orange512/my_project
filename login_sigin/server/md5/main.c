/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月28日 星期日 15时44分05秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "MD5.h"

int main(int argc, char* argv[])
{
    int i;
    MD5_CTX md5;
    MD5Init(&md5);                          //初始化用于md5加密的结构

    unsigned char encrypt[1024];     //存放于加密的信息
    unsigned char decrypt[17];       //存放加密后的结果
    scanf("%s",encrypt);                 //输入加密的字符

    MD5Update(&md5,encrypt,strlen((char *)encrypt));   //对欲加密的字符进行加密
    MD5Final(decrypt,&md5);                                             //获得最终结果

    printf("加密前:%s\n加密后:",encrypt);
    for(i=0; i<16; i++)
    {
        printf("%02x",decrypt[i]);

    }

    printf("\n\n\n加密结束!\n");

    return 0;

}

