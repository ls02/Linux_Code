CC=g++

.PHONY:all
all:client server

udp_client:client.cc
	$(CC) -o $@ $^ -std=c++11 -static

udp_server:server.cc
	$(CC) -o $@ $^ -std=c++11 -static

.PHONY:clean
clean:
	rm -rf server client
