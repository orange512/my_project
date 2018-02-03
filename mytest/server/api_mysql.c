/*************************************************************************
	> File Name: api_mysql.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月15日 星期一 14时50分10秒
 ************************************************************************/

#include"api_mysql.h"
MYSQL* init_mysql(MYSQL *mysql)
{
    mysql = mysql_init(mysql);
    if(mysql == NULL)
    {
        mysql_errno(mysql);
        printf("mysql_init error,%s\n",mysql_error(mysql));
        return NULL;
    }
    return mysql;
}
MYSQL* connect_mysql(MYSQL*mysql,char *ip,char *user,char *passwd,char *database)
{
    mysql = mysql_real_connect(mysql,ip,user,passwd,database,0,NULL,0);
    if(mysql == NULL)
    {
        printf("mysql_real_connect error,err is:%s\n",mysql_error(mysql));
        return NULL;
    }
    return mysql;
}
long affected_rows(MYSQL *mysql)
{
    return (long)mysql_affected_rows(mysql);
}
int query_mysql(MYSQL *mysql,const char *query)
{
    int ret = mysql_query(mysql,query);
    if(ret != 0)
    {
        printf("mysql_query error\n");
        return -1;
    }
    return 0;
}
MYSQL_RES* import_result(MYSQL* mysql)
{
    MYSQL_RES *result = mysql_store_result(mysql);
    if(result == NULL)
    {
        printf("mysql_store_result error\n");
        return NULL;
    }
    return result;
}
int count_result_rows(MYSQL_RES *result)
{
    return mysql_num_rows(result);
}
int count_result_fields(MYSQL_RES *result)
{
    return mysql_num_fields(result);
}
int display_table_content(MYSQL *mysql,MYSQL_RES *result)
{
    int field_num = mysql_field_count(mysql);
    MYSQL_FIELD *fields = mysql_fetch_fields(result);//列名
    printf("-------------------------------------\n");
    for(int i = 0 ; i < field_num;i++)
    {
        printf("%s \t",fields[i].name);
    }
    printf("\n------------------------------------\n");
    MYSQL_ROW row = NULL;
    while(row = mysql_fetch_row(result))
    {
        for(int i = 0 ; i < field_num;i++)
        {
            printf("%s \t",row[i]);
        }
        putchar(10);
    }
    mysql_free_result(result);
    return 0;
}
int close_mysql(MYSQL *mysql)
{
    mysql_close(mysql);
    printf("\n\nmysql close\n");
    return 0;
}
