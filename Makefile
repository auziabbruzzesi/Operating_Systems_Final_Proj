CC = /usr/bin/gcc

all: main_compile

main_compile: main.c;
	${CC} main.c -o simulation.exe
exec: main_compile;
	./simulation.exe
clean:
	rm *.exe