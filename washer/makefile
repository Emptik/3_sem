all: washer

washer: main.o tableware.o memory_manager.o
	g++ main.o tableware.o memory_manager.o -Wall -o ./washer
main.o: main.cpp
	g++ -Wall -c main.cpp
tableware.o: tableware.cpp
	g++ -Wall -c tableware.cpp
memory_manager.o: memory_manager.cpp
	g++ -Wall -c memory_manager.cpp
clean:
	rm -rf *.o ./washer
