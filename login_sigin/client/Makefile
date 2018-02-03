OBJ = client.o ./sigin/sigin.o tool/connect_server.o md5/MD5.o

###########################################

all:$(OBJ)
	gcc $(OBJ) -o client  -Wall  
%.o:%.c
	gcc -c $< -o $@ -I ./include/  -Wall
clean:
	rm -rf 'find -name "*.o"'
