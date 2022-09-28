.PHONY:all
all:myproc myshell

myproc:test.c
	gcc -o $@ $^

myshell:myshell.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -rf myproc myshell
