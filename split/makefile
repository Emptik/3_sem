all: adabada

adabada: main.o
	gcc main.o -Wall -o ./split.
main.o:
	gcc -Wall -c main.c
clean:
	rm -rf *.o ./split.
replace:
	mv ./split. ../bin/
