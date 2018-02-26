/*************************************************************************
	> File Name: group_info.h
	> Author: 
	> Mail: 
	> Created Time: 2018年02月22日 星期四 15时16分23秒
 ************************************************************************/

#ifndef _GROUP_INFO_H
#define _GROUP_INFO_H
#define MAX_GROUP_SIZE 8
struct group_info
{
    int is_use;
    char groupname[16];
    char name[20][16];
};
#endif
