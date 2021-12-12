procb:main.o procb.o
	gcc -o $@ $^
main.o:main.c
	gcc -c $<
proc.o:procb.c
	gcc -c $<

.PHONY:clean
clean:
	rm -f *.o procb
