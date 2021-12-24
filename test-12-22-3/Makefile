test3:test3.o
	gcc -o $@ $^
test3.o:test3.c
	gcc -c $<

.PHONY:clean
clean:
	rm -f *.o test3
