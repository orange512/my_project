/*************************************************************************
  > File Name: sql_pool.c
  > Author: 
  > Mail: 
  > Created Time: 2018年01月24日 星期三 12时19分35秒
 ************************************************************************/

#include<stdio.h>
#include"sql_pool.h"

/*创建连接池*/
SQL_CONN_POOL *sql_pool_create(int connect_pool_number, char ip[], int port, 
        char db_name[], char user[], char passwd[])
{
    SQL_CONN_POOL *sp = NULL;
    /* 错误输入检测 */
    if (connect_pool_number < 1)
    {
        printf("connect_pool_number < 1. defalut 1 \n");
        connect_pool_number = 1;

    }
    /* 为连接池划分内存空间 */
    if ((sp=(SQL_CONN_POOL *)malloc(sizeof(SQL_CONN_POOL))) == NULL)
    {
        printf("malloc SQL_CONN_POOL error.\n");
        return NULL;

    }

    sp->shutdown    = 0;              //开启连接池
    sp->pool_number = 0;              //连接数量
    sp->busy_number = 0;              //正在使用的连接数
    strcpy(sp->ip, ip);               //数据库IP
    sp->port = port;                  //数据库Port
    strcpy(sp->db_name, db_name);     //数据库名字
    strcpy(sp->user, user);           //使用用户名
    strcpy(sp->passwd, passwd);       //密码

    /* 创建连接 */
    if (connect_pool_number > POOL_MAX_NUMBER)
        connect_pool_number = POOL_MAX_NUMBER;

    for (int index=0; index < connect_pool_number; index++)
    {
        //创建失败， 自定义函数,创建节点函数;
        if (0 != create_db_connect(sp, &sp->sql_pool[index]))
        {
            //销毁连接池,自定义函数,销毁连接池;
            sql_pool_destroy(sp);
            return NULL;
        }
        //创建成功
        sp->sql_pool[index].index = index;
        sp->pool_number++;
        printf("create database pool connect:-%d-.\n",sp->sql_pool[index].index); 
    }

    return sp;
}
int create_db_connect(SQL_CONN_POOL *sp, SQL_NODE *node)
{
    int opt=1; //超时时间
    int res=0; //0正常 -1初始化失败 1 连接失败

    do
    {
        if (sp->shutdown == 1)  
            return -1;
        /* 节点加锁 */
        pthread_mutex_init(&node->lock, NULL);

        /* 初始化mysql对象 */
        if (NULL == mysql_init(&node->fd))
        {
            printf("mysql init error. \n");
            res = -1;
            break;
        }
        if (!(node->mysql_sock = mysql_real_connect(
                        &node->fd, sp->ip, sp->user, sp->passwd, sp->db_name, sp->port, NULL, 0)))
        {
            printf("can not connect to mysql.\n");
            node->sql_state = DB_DISCONN;
            res = 1;
            break;
        }
        //使用状态与连接状态
        node->used = 0;
        node->sql_state = DB_CONN;
        //设置自动连接开启
        mysql_options(&node->fd, MYSQL_OPT_RECONNECT, &opt);
        opt = 3;
        //设置连接超时时间为3s，3s未连接成功则超时
        mysql_options(&node->fd, MYSQL_OPT_CONNECT_TIMEOUT, &opt);
        res = 0;

    }while(0);

    return res;


}



void sql_pool_destroy(SQL_CONN_POOL *sp)
{
    printf("destroy sql pool ... ... \n");

    sp->shutdown = 1; //关闭连接池
    for (int index=0; index < sp->pool_number; index++)
    {
        if (NULL != sp->sql_pool[index].mysql_sock)
        {
            mysql_close(sp->sql_pool[index].mysql_sock);
            sp->sql_pool[index].mysql_sock = NULL;
        }
        sp->sql_pool[index].sql_state = DB_DISCONN; 
        sp->pool_number--;
    }
}



/*取出一个未使用的连接*/
SQL_NODE *get_db_connect(SQL_CONN_POOL *sp)
{
    //获取一个未使用的连接，用随机值访问index，保证每次访问每个节点的概率基本相同
    int start_index = 0, index = 0, i;
    int ping_res;     

    if (sp->shutdown == 1)
        return NULL;

    srand((int)time(0)); //根据当前时间生成随机数
    start_index = rand() % sp->pool_number; //访问的开始地址

    for (i=0; i < sp->pool_number; i++)
    {
        index = (start_index + i) % sp->pool_number;

        if (!pthread_mutex_trylock(&sp->sql_pool[index].lock))
        {
            if (DB_DISCONN == sp->sql_pool[index].sql_state)
            {
                //重新连接
                if (0 != create_db_connect(sp, &(sp->sql_pool[index])))
                {
                    //重新连接失败
                    release_node(sp, &(sp->sql_pool[index]));
                    continue;
                }
            }
            //检查服务器是否关闭了连接
            ping_res = mysql_ping(sp->sql_pool[index].mysql_sock);
            if (0 != ping_res)
            {
                printf("mysql ping error.\n");
                sp->sql_pool[index].sql_state = DB_DISCONN;
                release_node(sp, &(sp->sql_pool[index]));        //释放连接
            }
            else
            {
                sp->sql_pool[index].used = 1;
                sp->busy_number++;              //被获取的数量增1
                break ;                         //只需要一个节点
            }
        }
    }

    if (i == sp->pool_number)
        return NULL;
    else
        return &(sp->sql_pool[index]);

}







/*归回连接*/
void release_node(SQL_CONN_POOL *sp, SQL_NODE *node)
{
    node->used = 0;
    sp->busy_number--;
    pthread_mutex_unlock(&node->lock);
    printf("链接已释放\n");
}




/*增加或删除连接*/
SQL_CONN_POOL *changeNodeNum(SQL_CONN_POOL *sp, int op)  //增加或减少5个连接
{
    int Num = 5;      /* 此处可以用宏代替,根据自己的需求来实现 */
    int index;        
    int endindex;

    if (op == 1)  //增加    0减少
    {
        endindex = sp->pool_number + Num;
        /*创建连接*/
        for (index=sp->pool_number; index < endindex; index++)
        {
            //创建失败
            if (0 != create_db_connect(sp, &sp->sql_pool[index]))
            {
                //销毁连接池
                sql_pool_destroy(sp);
                return NULL;
            }
            //创建成功
            sp->sql_pool[index].index=index;  
            sp->pool_number++;
            printf("create database pool connect:-%d-.\n",sp->sql_pool[index].index); 
        }
    }
    else if (op == 0)
    {
        endindex = sp->pool_number - Num -1;
        //减少连接
        for (index=sp->pool_number-1; index>endindex && index>=0; index--)
        {       
            if (NULL != sp->sql_pool[index].mysql_sock)
            {
                mysql_close(sp->sql_pool[index].mysql_sock);
                sp->sql_pool[index].mysql_sock = NULL;
            }
            sp->sql_pool[index].sql_state = DB_DISCONN; 
            sp->pool_number--;
            printf("delete database pool connect:-%d-.\n",sp->sql_pool[index].index);
        }
    }

    return sp;
}



