myproc:test.o
	g++ -o $@ $^ -g
test.o:test.cc
	g++ -c $<
.PHONY:clear
clear:
	rm -rf *.o myproc
