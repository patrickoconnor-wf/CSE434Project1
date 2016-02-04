clean:
	rm server
	rm client

compile_server:
	clang++ --std=c++11 UDPServer/server.cpp -o server

compile_client:
		clang++ --std=c++11 UDPClient/client.cpp -o client

run_server: compile_server
	./server 9090

run_client: compile_client
	./client 127.0.0.1 $(ACTION) 9090

run_server_no_build:
	./server 9090

run_client_no_build:
	./client 127.0.0.1 $(ACTION) 9090
