.PHONY:all
all:tcp_server tcp_client 
tcp_server:server.cc 
	g++ -o $@ $^ -std=c++11 -lpthread
tcp_client:client.cc 
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY:clean 
clean:
	rm -rf tcp_server tcp_client
