all: useless

useless: main.o memory_manager.o split_dot.o processor_functions.o
	gcc main.o memory_manager.o split_dot.o processor_functions.o -Wall -o ./useless
main.o: main.c
	gcc -c main.c
memory_manager.o: memory_manager.c
	gcc -c memory_manager.c
split_dot.o: split_dot.c
	gcc -c split_dot.c
processor_functions.o: processor_functions.c
	gcc -c processor_functions.c
clean:
	rm -rf *.o ./useless
replace:
	mv useless ../bin/
