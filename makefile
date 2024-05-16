all: lab1

lab1: lab1.c functions.o
	gcc -g functions.o lab1.c -o lab1

main: main.c functions.o Format.o
	gcc -g functions.o Format.o main.c -o main

Saturated: Format.c Format.h
	gcc -g -c Format.c

functions: functions.c functions.h
	gcc -g -c functions.c

clean:
	rm -f *.o lab1 clasificaciones
