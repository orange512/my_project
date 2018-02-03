OBJ = server.o user_module/user_module.o user_module/forget_passwd.o user_module/login_server.o user_module/sigin_server.o  file_module/file_module.o file_module/down_file.o file_module/up_file.o chat_module/chat_module.o chat_module/group_chat.o chat_module/private_chat.o red_module/red_module.o red_module/recv_packet.o red_module/send_packet.o
#############################

all:$(OBJ)
	gcc $(OBJ) -o server -Wall
%.o:%.c
	gcc -c $< -o $@ -I ./include/  -Wall
clean:
	rm -rf `find -name "*.o"` server
