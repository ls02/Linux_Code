myproc:test.o
	g++ -o $@ $^
test.o:test.cc
	g++ -c $< -g
.PHONY:clear
clear:
	rm -rf *.o myproc
