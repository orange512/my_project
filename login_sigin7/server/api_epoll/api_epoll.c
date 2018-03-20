/*************************************************************************
	> File Name: api_epoll.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月27日 星期六 16时42分57秒
 ************************************************************************/
 #include"api_epoll.h"
 #include"../server.h"
 #include"../mychat/private_chat.h"
 #include"../mychat/group_chat.h"
extern struct cli_info cli_info[MAX_CLI_SIZE];
int setnonblocking( int fd )
{
    int old_option = fcntl( fd, F_GETFL );
    int new_option = old_option | O_NONBLOCK;
    fcntl( fd, F_SETFL, new_option );
    return old_option;
}

void addfd( int epollfd, int fd, int oneshot )
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if( oneshot )
    {
        event.events |= EPOLLONESHOT;
    }
    epoll_ctl( epollfd, EPOLL_CTL_ADD, fd, &event );
    setnonblocking( fd );
}

void reset_oneshot( int epollfd, int fd )
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
    epoll_ctl( epollfd, EPOLL_CTL_MOD, fd, &event );
}

void* worker( void* arg )
{
    int sockfd = ( (fds*)arg )->sockfd;
    int epollfd = ( (fds*)arg )->epollfd;
    printf( "start new thread to receive data on fd: %d\n", sockfd );
    char buf[ BUFFER_SIZE ];
    memset( buf, '\0', BUFFER_SIZE );
    while( 1 )
    {
        int ret = recv( sockfd, buf, BUFFER_SIZE-1, 0 );
        if( ret == 0 )
        {
            close( sockfd );
            printf( "foreiner closed the connection\n" );
            break;
        }
        else if( ret < 0 )
        {
            if( errno == EAGAIN )
            {
                reset_oneshot( epollfd, sockfd );
                printf( "read later\n" );
                break;
            }
        }
        else
        {
            printf( "get content: %s\n", buf );
            sleep( 5 );
        }
    }
    printf( "end thread receiving data on fd: %d\n", sockfd );
    return NULL;
}

void* mytask( void* arg )
{
    int sockfd = ( (fds*)arg )->sockfd;
    int epollfd = ( (fds*)arg )->epollfd;
    printf("start new thread to receive data on fd: %d\n", sockfd );
    msg_t msg;
    while( 1 )
    {
        memset(&msg, '\0',sizeof(msg_t) );
        int ret = recv( sockfd, &msg,sizeof(msg_t), 0 );
        if( ret == 0 )
        {
            for(int i = 0 ; i < MAX_CLI_SIZE;i++)
            {
                if(cli_info[i].cli_sockfd == sockfd)
                {
                    printf( "%s--foreiner closed the connection..\n",cli_info[i].cli_name );
                    fflush(stdout);
                    cli_info[i].cli_sockfd = -1;
                    memset(cli_info[i].cli_name,0,sizeof(cli_info[i].cli_name));
                    break;
                }
            }
            close( sockfd );
            break;
        }
        else if( ret < 0 )
        {
            if( errno == EAGAIN )
            {
                reset_oneshot( epollfd, sockfd );
                printf( "read later\n" );
                break;
            }
        }
        else
        {
            printf("msg.cmd = %d\n",msg.cmd);
           /* printf( "get content: %s\n", buf );
            sleep( 5 );*/
            switch(msg.cmd)
            {
                case SIGIN:
                sigin(sockfd,msg);
                break;
                case LOGIN:
                login(sockfd,msg);
                printf("登录jeishu\n");
                break;
                printf("msg.cmd = %d\n",msg.cmd);
                case PRIVATE_CHAT:
                private_chat(sockfd,msg);
                break;
                case GROUP_CHAT:
                group_chat(sockfd,msg);
                break;
            }

        }
    }
    printf( "end thread receiving data on fd: %d\n", sockfd );
    return NULL;
}
