#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <cstdlib>

#include "dishwasher.h"
#include "../macro.h"
#include "../message_object.h"

void wash(int time) {
	for(int i = 0; i < time; i++);
}
	
void dishwasher_interact(class dishwasher *all_dishes) {
	
	char pathname[]= "../macro.h";
	key_t key = 0;
	key = ftok(pathname, 0);
	int msqid = msgget(key, 0666 | IPC_CREAT);
	
	class message mes[QUANTITY_OF_DISH_TYPES] = {};
	int message_number = 0;
	int time = 0;
	
	for(int i = 0; i < QUANTITY_OF_DISH_TYPES; i++) {
		
		mes[i] = message(all_dishes[i].get_dish_type());
		time = all_dishes[i].get_wash_time();
		int number = all_dishes[i].get_number_of_dishes();
		
		for(int j = 0; j < number; j++) {
			wash(time);
			msgsnd(msqid, &mes[i], sizeof(class message) - sizeof(long), 0);
		}
		
		message_number++;
	}
}
