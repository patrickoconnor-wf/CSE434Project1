server_source_list = UDPServer/server.cpp Ports/ports.cpp Packet/packet.cpp
client_source_list = UDPClient/client.cpp Ports/ports.cpp Packet/packet.cpp
ACTION = This_should_be_unused

all: clean compile_server compile_client

clean:
	if [ -a server ]; \
		then \
			rm server; \
	fi; \
	if [ -a client ]; \
		then \
			rm client; \
	fi;

compile_server:
	clang++ --std=c++11 $(server_source_list) -o server

compile_client:
	clang++ --std=c++11 $(client_source_list) -o client

run_server: compile_server
	# TODO: Make server port a constant. Probably last available port
	./server 9090

run_client: compile_client
	./client 127.0.0.1 $(ACTION) 9090

run_server_no_build:
	./server 9090

run_client_no_build:
	./client 127.0.0.1 $(ACTION) 9090
