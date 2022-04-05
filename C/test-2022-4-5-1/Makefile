myproc:test.o
	gcc -o $@ $^
test.o:test.c
	gcc -c $<

.PHONY:clear
clear:
	rm -rf *.o myproc
