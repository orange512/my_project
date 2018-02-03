/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月24日 星期三 12时34分08秒
 ************************************************************************/

#include<stdio.h>
#include"sql_pool.h"
#include"../API_MYSQL/api_mysql.h"
int main()  
{  
    SQL_CONN_POOL *sp = sql_pool_create(10, "192.168.0.128", 3306, "weChat", "root", "950512");  
    SQL_NODE *node  = get_db_connect(sp);  
    SQL_NODE *node2 = get_db_connect(sp);

    if (NULL == node)  
    {  
        printf("get sql pool node error.\n");  
        return -1;  
    } 
    printf("--%d-- \n", node->index);
    printf("busy--%d--\n", sp->busy_number);
    
    query_mysql(&(node->fd),"select *from usertable;");
    MYSQL_RES *result = import_result(&(node->fd));
    display_table_content(&(node->fd),result);
    /*if (mysql_query(&(node->fd), "select * from usertable;"))
    {                                                    
        printf("query error.\n");                                     
        return -1;                                      
    }
    else  
    printf("succeed!\n");*/  

    changeNodeNum(sp, 0);//减少
    changeNodeNum(sp, 1);//增加
    sql_pool_destroy(sp);

    return 0;  
}
