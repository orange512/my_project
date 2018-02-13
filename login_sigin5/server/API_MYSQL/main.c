/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月15日 星期一 16时46分26秒
 ************************************************************************/

#include<stdio.h>
#include"api_mysql.h"

int main()
{
    MYSQL* mysql;
    mysql = init_mysql(mysql);
    mysql = connect_mysql(mysql,"localhost","root","950512","student");
    query_mysql(mysql,"select *from stu");
    MYSQL_RES *result = import_result(mysql);
    printf("row == %d\n",count_result_rows(result));
    printf("cloumn == %d\n",count_result_fields(result));
    display_table_content(mysql,result);
    close_mysql(mysql);
}
