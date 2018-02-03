OBJ = client.o login/login.o tool/send_server.o user/user_main.o user/file_center.o user/up_file.o

###########################################

all:$(OBJ)
	gcc $(OBJ) -o client -Wall 
%.o:%.c
	gcc -c $< -o $@ -I ./include/  -Wall
clean:
	rm -rf 'find -name "*.o"' client
