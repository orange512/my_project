/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月27日 星期六 12时53分55秒
 ************************************************************************/

#include"server.h"
#define SERVERPORT 9000
#define SERVERIP "127.0.0.1"
#include"./include/cli_info.h"
threadpool_t pool;
SQL_CONN_POOL *sp ;  
struct cli_info cli_info[MAX_CLI_SIZE] = { -1 };
int create_sock()
{
    //socket
    int listenfd;
    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
        ERR_EXIT("socket");

    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVERIP);
    if(server_addr.sin_addr.s_addr == INADDR_NONE)
    {
        struct hostent *host = NULL;
        if(NULL != (host = gethostbyname(SERVERIP)))
        {
            memcpy(&(server_addr.sin_addr.s_addr), host->h_addr,host->h_length);
            server_addr.sin_family = host->h_addrtype;
        }
        else
        {
            ERR_EXIT("域名或IP地址错误,请检查域名或IP地址是否正确!");
        }
    }
    int on = 1;

    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))< 0)//地址重复利用
        ERR_EXIT("setsockopt");
    //bind
    if(bind(listenfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
        ERR_EXIT("bind");

    return listenfd;

}

int my_epoll(int listenfd)
{
    struct epoll_event events[ MAX_EVENT_NUMBER  ];
    int epollfd = epoll_create( 5  );
    assert( epollfd != -1  );
    addfd( epollfd, listenfd, 0 );//listenfd要连续触发要LT模式
    threadpool_init(&pool,10);
    while(1)
    {
        int ret = epoll_wait( epollfd, events, MAX_EVENT_NUMBER, -1  );
        if ( ret < 0  )
        {
            printf( "epoll failure\n"  );
            break;
        }
        for ( int i = 0; i < ret; i++  )
        {
            int sockfd = events[i].data.fd;
            if ( sockfd == listenfd )
            {
                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof( client_address  );
                int connfd = accept( listenfd, ( struct sockaddr*  )&client_address, &client_addrlength  );
                addfd( epollfd, connfd, 1);
            }
            else if ( events[i].events & EPOLLIN  )
            {
                fds fds_for_new_worker;
                fds_for_new_worker.epollfd = epollfd;
                fds_for_new_worker.sockfd = sockfd;
                threadpool_add_task( &pool, mytask, ( void* )&fds_for_new_worker );
            }
            else
            {
                printf( "something else happened \n"  );
            }

        }
        printf("一层循环完毕\n");
    }
    close(listenfd);
    return 0;
}
int server_start()
{
    int listenfd = create_sock();
    //listen
    if(listen(listenfd,SOMAXCONN) < -1)
        ERR_EXIT("listen");
    my_epoll(listenfd);
    return 0;
}
int main()
{
    for(int i = 0;i < MAX_CLI_SIZE;i++)
    {
        cli_info[i].cli_sockfd = -1;
        memset(cli_info[i].cli_name,0,sizeof(cli_info[i].cli_name));
    }
    sp =sql_pool_create(10, "localhost", 3306, "test", "root", "950512");
    server_start(); 
    sql_pool_destroy(sp);
    threadpool_destroy(&pool);
    return 0;
}


