.PHONY:all
all:tcp_server tcp_client

tcp_server:tcp_server.cc
	g++ -o $@ $^ 

tcp_client:tcp_client.cc
	g++ -o $@ $^ 

.PHONY:clean
clean:
	rm -rf tcp_server tcp_client



#CC=g++
#
#.PHONY:all
#all:tcp_client tcp_server
#
#tcp_client:tcp_client.cc
#	$(CC) -o $@ $^ -std=c++11 -static
#
#tcp_server:tcp_server.cc
#	$(CC) -o $@ $^ -std=c++11
#
#.PHONY:clean
#clean:
#	rm -f tcp_client tcp_server
