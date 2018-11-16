#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "tableware.h"	

#define QUANTITY_OF_DISH_TYPES 3
#define STRING_MAX_SIZE 100

using namespace std;
void read_input(char *input_string);
void write_information_to_classes(char *dish_information, class tableware all_dishes[]);

int main() {
	class tableware all_dishes[QUANTITY_OF_DISH_TYPES] = {};
	char input_string[STRING_MAX_SIZE] = {0};
	read_input(input_string);
	write_information_to_classes(input_string, all_dishes);
}
