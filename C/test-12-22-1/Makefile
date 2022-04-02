test1:test1.o
	gcc -o $@ $^
test.o:test.c
	gcc -c $<

.PHONY:clean
clean:
	rm -f *.o test1
