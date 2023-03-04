.PHONY:all
all:udp_server udp_client

udp_server:server.cc
	g++ -o $@ $^ -std=c++11
udp_client:client.cc 
	g++ -o $@ $^ -std=c++11;

.PHONY:clean
clean:
	rm -rf udp_server udp_client
