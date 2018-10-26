all: thread

thread: main.c
	gcc -Wall -O2 -pthread -o "thread" "main.c"
clean:
	rm -rf *.o ./thread
replace:
	mv ./thread ../bin/
