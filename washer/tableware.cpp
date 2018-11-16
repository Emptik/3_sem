#include <cstring> 
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include "tableware.h"	
#define QUANTITY_OF_DISH_TYPES 3
#define STRING_MAX_SIZE 100

using namespace std;

tableware::tableware() {
	dish_type = 0;
	wash_time = 0;
	number_of_dishes = 0;
}

tableware::tableware(char * array) {
	dish_type = strtok(array, ":");
	push_wash_time();
	push_number_of_dishes();
}

void tableware::push_wash_time() {
	char *check = strtok(0, ":");
	if(check) wash_time = atoi(check);
	else {
		cout << "push_wash_time try to push NULL" << endl;
		exit(1);
	}
}

void tableware::push_number_of_dishes() {
	char *check = strtok(0, "\n");
	if(check) number_of_dishes = atoi(check);
	else {
		cout << "push_number_of_dishes try to push NULL" << endl;
		exit(2);
	}
}

void tableware::pull_all() {
	cout << "dish_type: " << dish_type << endl;
	cout << "wash_time: " << wash_time << endl;
	cout << "number_of_dishes: " << number_of_dishes << endl;
}

void write_information_to_classes(char *dish_information, class tableware all_dishes[]) { 
	all_dishes[0] = tableware(strtok(dish_information,"\0"));
	for(int i = 1; i < QUANTITY_OF_DISH_TYPES; i++) {
		all_dishes[i] = tableware(strtok(NULL, "\0"));
	}
}
