all: lab1

main: lab1.c functions.o
	gcc -g functions.o lab1.c -o lab1

functions: functions.c functions.h
	gcc -g -c functions.c
saturation: s

binary:

gray:

clean:
	rm -f *.o main clasificaciones
