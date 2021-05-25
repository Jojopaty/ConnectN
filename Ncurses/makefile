all: clean ncurses run

clean:
	rm grass.exe
ncurses: ncurses.c
	gcc -lncursesw grass.c -o grass.exe

run:
	./grass.exe
