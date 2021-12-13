mytest1:mytest.o
	gcc -o $@ $^
mytest.o:mytest.c
	gcc -c $<

.PHONY:clean
clean:
	rm -f *.o test
