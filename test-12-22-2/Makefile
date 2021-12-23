test2:test2.o
	gcc -o $@ $^
test2.o:test2.c
	gcc -c $<

.PHONY:clean
clean:
	rm -f *.o test2
