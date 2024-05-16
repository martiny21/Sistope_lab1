all: main

main: main.c functions.o
	gcc -g functions.o main.c -o main

functions: functions.c functions.h
	gcc -g -c functions.c
saturation: s

binary:

gray:

clean:
	rm -f *.o main clasificaciones
