#include <cstring> 
#include <iostream>
#include <cstdlib>
#include <assert.h>

#include "dishwasher.h"
#include "../macro.h"

dishwasher::dishwasher() {
	dish_type = 0;
	wash_time = 0;
	number_of_dishes = 0;
}

dishwasher::dishwasher(char * array) {
	dish_type = strtok(array, ":");
	push_wash_time();
	push_number_of_dishes();
}

void dishwasher::push_wash_time() {
	char *check = strtok(0, ":");
	if(check) wash_time = atoi(check);
	else {
		cout << "push_wash_time: try to push NULL" << endl;
		exit(1);
	}
}

void dishwasher::push_number_of_dishes() {
	char *check = strtok(0, "\n");
	if(check) number_of_dishes = atoi(check);
	else {
		cout << "push_number_of_dishes: try to push NULL" << endl;
		exit(2);
	}
}

void dishwasher::show_all_values() {
	cout << "dish_type: " << dish_type << endl;
	cout << "wash_time: " << wash_time << endl;
	cout << "number_of_dishes: " << number_of_dishes << endl;
}

void write_information_to_dishwasher(char *dish_information, class dishwasher all_dishes[]) { 
	all_dishes[0] = dishwasher(strtok(dish_information,"\0"));
	for(int i = 1; i < QUANTITY_OF_DISH_TYPES; i++) {
		all_dishes[i] = dishwasher(strtok(NULL, "\0"));
	}
}
