all: clean ncurses run

ncurses: ncurses.c
	gcc -lncurses ncurses.c -o ncurses.exe
clean:
	rm ncurses.exe
run:
	./ncurses.exe
