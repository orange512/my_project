/*************************************************************************
	> File Name: api_redis.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月15日 星期一 18时11分48秒
 ************************************************************************/

#include<stdio.h>
#include"api_redis.h"
redisContext* connect_redisContext(char *ip,int port)
{
    redisContext *c = redisConnect(ip,port);
    if(c->err)
    {
        redisFree(c);
        printf("连接redis失败\n");
        return NULL;
    }
    return c;
}
int set_redis(redisContext *c,char *command)
{
    redisReply *r = (redisReply *)redisCommand(c,command);
    if(NULL == r)
    {
        printf("执行命令失败\n");
        redisFree(c);
        return -1;
    }
    if(!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK") ==0))
    {
        printf("执行command%s failed\n",command);
        freeReplyObject(r);
        redisFree(c);
        return -1;
    }
    freeReplyObject(r);
}
int show_integer(redisContext *c,char *command)
{
    redisReply *r = (redisReply *)redisCommand(c,command);
    if(r->type != REDIS_REPLY_INTEGER)
    {
        printf("执行%s failed\n",command);
        freeReplyObject(r);
        redisFree(c);
        return -1;
    }
    freeReplyObject(r);
    return r->integer;
}
int get_redis(redisContext *c,char *command,char **value)
{
    redisReply *r = (redisReply *)redisCommand(c,command);
    if(r->type != REDIS_REPLY_STRING)
    {
        printf("执行%s failed\n",command);
        freeReplyObject(r);
        redisFree(c);
        return -1;
    }
    if(r->type == REDIS_REPLY_NIL)
    {
        freeReplyObject(r);
        redisFree(c);
        return -2;
    }
    *value = (char *)malloc(sizeof(r->str));
    sprintf(*value,"%s",r->str);
    printf("%s\n",*value);
    freeReplyObject(r);
    return 0;
}
int redis_free(redisContext *c)
{
    redisFree(c);
}
