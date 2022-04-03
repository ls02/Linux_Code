c:test.o proc.o
	gcc -o $@ $^
test.o:test.c
	gcc -c test.c
proc.o:proc.c
	gcc -c proc.c
.PHONY:clear
clear:
	rm -rf *.o c
