OBJ = client.o ./sigin/sigin.o ./login/login.o tool/connect_server.o md5/MD5.o \
	  ./log_sig/log_sig.o ./no_echo_passwd/noecho_passwd.o

###########################################

all:$(OBJ)
	gcc $(OBJ) -o client  -Wall  
%.o:%.c
	gcc -c $< -o $@ -I ./include/  -Wall
clean:
	rm -rf 'find -name "*.o"'
