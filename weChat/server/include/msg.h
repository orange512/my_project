/*************************************************************************
	> File Name: server.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月26日 星期四 19时37分25秒
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H
//cmd
#define  USER_MODULE     1
#define  FILE_MODULE     2
#define  CHAT_MODULE     3
#define  RED_MODULE      4

typedef struct msg
{
    short int cmd;
    short int key;
    char val[400];
}MSG;

#endif
