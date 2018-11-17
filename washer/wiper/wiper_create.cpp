#include <cstring> 
#include <iostream>
#include <cstdlib>
#include <assert.h>

#include "wiper.h"
#include "../macro.h"

wiper::wiper() {
	dish_type = 0;
	wipe_time = 0;
}

wiper::wiper(char * array) {
	dish_type = strtok(array, ":");
	push_wipe_time();
}

void wiper::push_wipe_time() {
	char *check = strtok(0, "\n");
	if(check) wipe_time = atoi(check);
	else {
		cout << "push_wipe_time: try to push NULL" << endl;
		exit(3);
	}
}

void wiper::show_all_values() {
	cout << "dish_type: " << dish_type << endl;
	cout << "wipe_time: " << wipe_time << endl;
}

void write_information_to_wiper(char *dish_information, class wiper all_dishes[]) { 
	all_dishes[0] = wiper(strtok(dish_information,"\0"));
	for(int i = 1; i < QUANTITY_OF_DISH_TYPES; i++) {
		all_dishes[i] = wiper(strtok(NULL, "\0"));
	}
} 

