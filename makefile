all: ncurses

clean:
	rm ConnectN.exe
build: main.c
	gcc -Wall -Werror -g -I . main.c ConnectN.c gui.c -o ConnectN.exe -lncursesw

install:
	sudo apt-get install libncurses5-dev libncursesw5-dev

run:
	./ConnectN.exe
