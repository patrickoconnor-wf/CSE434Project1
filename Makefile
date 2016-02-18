server_source_list = UDPServer/server.cpp Ports/ports.cpp Packet/packet.cpp \
										 Utils/network_utils.cpp Utils/file_utils.cpp
client_source_list = UDPClient/client.cpp Ports/ports.cpp Packet/packet.cpp \
										 Utils/network_utils.cpp Utils/file_utils.cpp
test_source_list = Ports/ports.cpp Packet/packet.cpp Utils/network_utils.cpp \
									 test.cpp
ACTION = This_should_be_unused
server_port = 4923

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
	# Running server on port $(server_port)
	./server $(server_port)

run_client: compile_client
	./client 127.0.0.1 $(ACTION)

run_server_no_build:
	./server $(server_port)

run_client_no_build:
	./client 127.0.0.1 $(ACTION)

compile_test:
	clang++ --std=c++11 $(test_source_list) -o test
