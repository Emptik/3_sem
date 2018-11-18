#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "wiper.h"
#include "../macro.h"
#include "../message_object.h"

void wipe(int time) {
	for(int i = 0; i < time; i++);
}

void wiper_interact(class wiper *all_dishes) {
	
	char pathname[]= "../macro.h";
	key_t key = 0;
	key = ftok(pathname, 0);
	int msqid = msgget(key, 0666 | IPC_CREAT);
	class message mes;
	
	while(1) {
		msgrcv(msqid, &mes, sizeof(class message) - sizeof(long), 1, 0);
		for(int i = 0; i < QUANTITY_OF_DISH_TYPES; i++) {
			if(strcmp(mes.get_dish(), all_dishes[i].get_dish_type()) == 0) {
				wipe(all_dishes[i].get_wipe_time());
				break;
			}
		}
	}
}
