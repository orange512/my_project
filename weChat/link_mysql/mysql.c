/*************************************************************************
	> File Name: mysql.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月17日 星期二 21时28分06秒
 ************************************************************************/
#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
int main()
{
    int ret=0;
    MYSQL mysql;//MYSQL句柄
    MYSQL *connect = NULL;
    connect = mysql_init(&mysql);//初始化
    if(connect == NULL)
    {
        ret = mysql_errno(&mysql);
        printf("mysql_init error,%s\n",mysql_error(&mysql));
        return ret;
    }
    printf("mysql_init ok...\n");
    connect = mysql_real_connect(connect,"localhost","root","950512","student",0,NULL,0);//连接数据库
    if(connect == NULL)
    {
        ret = mysql_errno(&mysql);
        printf("mysql_real_connect error,err is:%s\n",mysql_error(&mysql));
        return ret;
    }
    printf("mysql_real_connect ok...\n");
    const char *query = "select *from stu";
    ret = mysql_query(connect,query);//查询
    if(ret != 0)
    {
        printf("mysql_query error\n");
        return ret;
    }
    MYSQL_RES *result = mysql_store_result(&mysql);//结果集
    if(result == NULL)
    {
        printf("mysql_store_result error\n");
        return -1;
    }
    int field_num = mysql_field_count(&mysql);
    MYSQL_FIELD *fields = mysql_fetch_fields(result);//获取列名
    printf("-------------------------------------\n");
    for(int i = 0 ; i < field_num;i++)
    {
        printf("%s \t",fields[i].name);
    }
    printf("\n------------------------------------\n");
    //获取表内容
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
    mysql_close(connect);
    printf("mysql_close\n");
    return ret;
}
