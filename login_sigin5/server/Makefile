OBJ = server.o api_epoll/api_epoll.o threadpool/thread_pool.o threadpool/condition.o \
	  API_MYSQL/api_mysql.o ./SQL_POLL/sql_pool.o ./sigin/sigin.o ./login/login.o \
	  mychat/private_chat.o
###########################################

all:$(OBJ)
	gcc $(OBJ) -o server -lpthread -Wall  -I /usr/include/mysql -L /usr/lib/mysql -l mysqlclient -lz -lm 
%.o:%.c
	gcc -c $< -o $@ -I ./include/  -Wall
clean:
	rm -rf $(OBJ)
