all: main

main: main.c functions.o
	gcc functions.o main.c -o main

functions: functions.c
	gcc -g -c functions.c
saturation: s

binary:

gray:

clean:
	rm -f *.o main
