/*************************************************************************
	> File Name:cli_info.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月03日 星期六 15时35分41秒
 ************************************************************************/

#ifndef _CLI_INFO_H
#define _CLI_INFO_H
#define MAX_CLI_SIZE 100
struct cli_info
{
    int cli_sockfd;
    char cli_name[16];
};//以后改进用链表，可以支持更多的用户
#endif
