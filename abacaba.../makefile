all: abacaba

abacaba: main.o
	gcc main.o -Wall -o ./abacaba
main.o:
	gcc -Wall -c main.c
clean:
	rm -rf *.o abacaba
replace:
	mv abacaba ../bin/
