my_shell:mini_shell.o
	gcc -o $@ $^
mini_shell.o:mini_shell.s
	gcc -c -o $@ $^
mini_shell.s:mini_shell.i
	gcc -S -o $@ $^
mini_shell.i:mini_shell.c
	gcc -E -o $@ $^

.PHONY:clean
clean:
	rm -rf *.i *.s *.o my_shell
