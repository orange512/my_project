/*************************************************************************
	> File Name: api_mysql.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月15日 星期一 15时46分33秒
 ************************************************************************/

#ifndef _API_MYSQL_H
#define _API_MYSQL_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
MYSQL* init_mysql(MYSQL* mysql);//初始化mysql
int count_result_rows(MYSQL_RES *result);//统计行数
int count_result_fields(MYSQL_RES *result);//统计列数
MYSQL_ROW get_row_result(MYSQL_RES *result);
int count_mysql_field(MYSQL* mysql);
MYSQL* connect_mysql(MYSQL* connect,char *ip,char *user,char *passwd,char *database);//连接mysql
int query_mysql(MYSQL *connect,const char *query);//执行sql
long affected_rows(MYSQL *mysql);
MYSQL_RES* import_result(MYSQL* mysql);//将查询结果输出到结果集
int display_table_content(MYSQL* mysql,MYSQL_RES *result);//显示结果集
int close_mysql(MYSQL *mysql);//关闭mysql
MYSQL *finished_mysql();
#endif
