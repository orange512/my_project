/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年02月02日 星期五 19时04分24秒
 ************************************************************************/

#include<stdio.h>
#include"noecho_passwd.h"
int main()
{
    unsigned char passwd[16];
    noecho_passwd(passwd); 
    printf("\npasswd = %s\n",passwd);
}
