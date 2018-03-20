/*************************************************************************
	> File Name: api_redis.h
	> Author: 
	> Mail: 
	> Created Time: 2018年01月15日 星期一 18时32分39秒
 ************************************************************************/

#ifndef _API_REDIS_H
#define _API_REDIS_H
#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<stdarg.h>
#include<string.h>
#include<assert.h>
#include<hiredis/hiredis.h>
redisContext* connect_redisContext(char *ip,int port);
int set_redis(redisContext *c,char *command);
int show_integer(redisContext *c,char *command);
int get_redis(redisContext *c,char *command,char **value);
int redis_free(redisContext *c);
#endif
