#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <cstdlib>
#include <cstdio>

#include "dishwasher.h"
#include "../macro.h"

void wash(int time) {
	for(int i = 0; i < time; i++);
}

void write_in_fifo(int fd, char *input) {
	if(write(fd, input, MAX_TYPE_SIZE) < 0) {
		perror("write_dishwasher");
	}
}
	
	
void dishwasher_interaction(class dishwasher *all_types) {
	int fd = 0;
	if(mkfifo("IPC_fifo_file", 0777)) {
		perror("mkfifo_dishwasher");
		exit(21);
	}
	fd = open("IPC_fifo_file", O_WRONLY);
	if(fd == -1) {
		 perror("open_fifo_in_dishwasher");
	 }
	 for(int i = 0; i < QUANTITY_OF_DISH_TYPES; i++) {
		 wash(all_types[i].get_wash_time());
		 write_in_fifo(fd, all_types[i].get_dish_type());
	 }
 }
