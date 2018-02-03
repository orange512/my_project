/*************************************************************************
	> File Name: noecho_passwd.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月02日 星期五 19时03分01秒
 ************************************************************************/

#ifndef _NOECHO_PASSWD_H
#define _NOECHO_PASSWD_H
#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>
#include<errno.h>
#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)
int set_disp_mode(int fd,int option);
int getpasswd(unsigned char *passwd,int size);
int noecho_passwd(unsigned char *passwd);
#endif
