/*************************************************************************
	> File Name: sql_pool.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月24日 星期三 12时16分56秒
 ************************************************************************/

#ifndef _SQL_POOL_H
#define _SQL_POOL_H
#define IP_LEN      15
#define DBNAME_LEN  64
#define DBUSER_LEN  64
#define PASSWD_LEN  64
#define POOL_MAX_NUMBER 20
#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<pthread.h>
#include<string.h>
typedef struct _SQL_NODE SQL_NODE;                /* 连接节点 */
typedef struct _SQL_CONN_POOL SQL_CONN_POOL;      /* 连接池 */

/* 连接节点 */
typedef struct _SQL_NODE{
    MYSQL            fd;                  /* MYSQL对象文件描述符 */
    MYSQL            *mysql_sock;         /* 指向已经连接的MYSQL的指针 */
    pthread_mutex_t  lock;                /* 互斥锁; 用在线程对数据的操作限制*/
    int              used;                /* 使用标志 */
    int              index;               /* 下标 */
    enum{                                 /* 连接状态 */
         DB_DISCONN, DB_CONN          
        }sql_state;


}SQL_NODE;

/* 连接池 */
typedef struct _SQL_CONN_POOL{
    int        shutdown;                   /* 是否关闭 */
    SQL_NODE   sql_pool[POOL_MAX_NUMBER];  /* 一堆连接 */
    int        pool_number;                /* 连接数量 */
    int        busy_number;                /* 被获取了的连接数量 */
    char       ip[IP_LEN+1];               /* 数据库的ip */
    int        port;                       /* 数据库的port,一般是3306 */
    char       db_name[DBNAME_LEN+1];      /* 数据库的名字 */
    char       user[DBUSER_LEN+1];         /* 用户名 */
    char       passwd[PASSWD_LEN+1];       /* 密码 */

}SQL_CONN_POOL;



/*创建连接池*/
SQL_CONN_POOL *sql_pool_create(int connect_pool_number, char ip[], int port, 
                               char db_name[], char user[], char passwd[]);
/*节点创建连接*/
int create_db_connect(SQL_CONN_POOL *sp, SQL_NODE *node);
/*销毁连接池*/
void sql_pool_destroy(SQL_CONN_POOL *sp);
/*取出一个未使用的连接*/
SQL_NODE *get_db_connect(SQL_CONN_POOL *sp);
/*归回连接*/
void release_node(SQL_CONN_POOL *sp, SQL_NODE *node);
/*增加或删除连接*/
SQL_CONN_POOL *changeNodeNum(SQL_CONN_POOL *sp, int op);

#endif
