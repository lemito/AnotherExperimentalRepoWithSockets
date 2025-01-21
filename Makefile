all: build_server build_client

build_server:
	clang++ server.cpp -o server

build_client:
	clang++ client.cpp -o client

run: build_server build_client
	./server &
	./client
