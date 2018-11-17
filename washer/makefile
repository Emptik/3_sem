all: dishwasher wiper

wiper: wiper.o wiper_functions.o memory_manager.o
	g++ wiper.o wiper_functions.o memory_manager.o -Wall -o "wiper.out"
	mv ./wiper.out build/
dishwasher: dishwasher.o dishwasher_functions.o memory_manager.o
	g++ dishwasher_functions.o dishwasher.o memory_manager.o -Wall -o "dishwasher.out"
	mv ./dishwasher.out build/

wiper.o: wiper/wiper.cpp
	g++ -Wall -c wiper/wiper.cpp
wiper_functions.o: wiper/wiper_functions.cpp
	g++ -Wall -c wiper/wiper_functions.cpp

dishwasher.o: dishwasher/dishwasher.cpp
	g++ -Wall -c dishwasher/dishwasher.cpp
dishwasher_functions.o: dishwasher/dishwasher_functions.cpp
	g++ -Wall -c dishwasher/dishwasher_functions.cpp

memory_manager.o: memory_manager.cpp
	g++ -Wall -c memory_manager.cpp
clean:
	rm -rf *.o
