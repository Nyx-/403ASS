CLIENT_LIB=Client/lib
SERVER_LIB=Server/lib
EXE_LOC=bin/
FLAGS= 

all: clean COMPILE_SERVER COMPILE_CLIENT

#uncomment the server libraries when we actually implement them
COMPILE_SERVER: #SERVER_LIBRARIES
	mkdir -p $(EXE_LOC)
	gcc Server/server.c $(wildcard libs/*) -o $(EXE_LOC)/server -lpthread $(FLAGS)
	make clean_serv

SERVER_LIBRARIES: 
	mkdir libs/
	for dir in $(SERVER_LIB); do \
		cd $$dir; \
		gcc $(FLAGS) -c *.c; \
		mv *.o ../../libs; \
		cd -; \
	done

#uncomment the client libraries when we actually implement them
COMPILE_CLIENT: #CLIENT_LIBRARIES
	mkdir -p $(EXE_LOC)
	gcc Client/client.c $(wildcard libc/*) -o $(EXE_LOC)/client -lpthread $(FLAGS)
	make clean_cli

CLIENT_LIBRARIES: 
	mkdir libc/
	for dir in $(CLIENT_LIB); do \
		cd $$dir; \
		gcc $(FLAGS) -c *.c ; \
		mv *.o ../../libc; \
		cd -; \
	done

clean: clean_serv clean_cli

clean_serv:
	rm -rf libs/

clean_cli: 
	rm -rf libc/
