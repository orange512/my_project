/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月03日 星期二 11时45分49秒
 ************************************************************************/

#include<stdio.h>
#include"user.h"
#include"client.h"
#include"user_main.h"//普通用户
int main()
{
    struct user user;
    while(1)
    {
        user = login_main();
        user.type = USER;
        switch(user.type)
        {
            case USER:
            user_main(&user);
            break;
            case ROOT:
            // root_main();
            break;
            default:
            break;
        }
    }
    return 0;

}
