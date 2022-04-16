myporc:test.o
	gcc -o $@ $^
test.o:test.c
	gcc -g -c $< -std=c99
.PHONY:clear
clear:
	rm -rf *.o myporc
