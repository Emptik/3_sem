all: thread

thread: main.c
	gcc -Wall -pthread -o "thread" "main.c"
clean:
	rm -rf *.o ./thread
replace:
	mv ./thread ../bin/
