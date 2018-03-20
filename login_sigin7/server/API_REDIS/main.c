/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月15日 星期一 18时35分36秒
 ************************************************************************/

#include"api_redis.h"

int main()
{
    redisContext *c = connect_redisContext("127.0.0.1",6379);
    //set_redis(c,"set k1 hello");
    //printf("show_integer%d\n",show_integer(c,"strlen k1"));
    char *value;    
    get_redis(c,"hget haha123 totalmoney",&value);
    printf("get k1 = %s",value);
    int a = atoi(value);
    printf("a = %d\n",a);
    free(value);
    redis_free(c);
}
