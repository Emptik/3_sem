all: dishwasher wiper

wiper: wiper.o wiper_create.o memory_manager.o wiper_IPC.o
	g++ wiper.o wiper_create.o memory_manager.o wiper_IPC.o  -Wall -o "wiper.out"
	mv ./wiper.out build/
dishwasher: dishwasher.o dishwasher_create.o memory_manager.o dishwasher_IPC.o
	g++ dishwasher_create.o dishwasher.o memory_manager.o dishwasher_IPC.o -Wall -o "dishwasher.out"
	mv ./dishwasher.out build/

wiper.o: wiper/wiper.cpp
	g++ -Wall -c wiper/wiper.cpp
wiper_create.o: wiper/wiper_create.cpp
	g++ -Wall -c wiper/wiper_create.cpp
wiper_IPC.o: wiper/wiper_IPC.cpp
	g++ -Wall -c wiper/wiper_IPC.cpp

dishwasher.o: dishwasher/dishwasher.cpp
	g++ -Wall -c dishwasher/dishwasher.cpp
dishwasher_create.o: dishwasher/dishwasher_create.cpp
	g++ -Wall -c dishwasher/dishwasher_create.cpp
dishwasher_IPC.o: dishwasher/dishwasher_IPC.cpp
	g++ -Wall -c dishwasher/dishwasher_IPC.cpp

memory_manager.o: memory_manager.cpp
	g++ -Wall -c memory_manager.cpp
clean:
	rm -rf *.o
