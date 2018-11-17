#include <iostream>
#include <cstdlib>
#include <cstring>

#include "dishwasher.h"
#include "../macro.h"

void read_input(char *input_string);
void write_information_to_dishwasher(char *dish_information, class dishwasher all_dishes[]);
void dishwasher_interact(class dishwasher *all_dishes);

int main() {
	class dishwasher all_dishes[QUANTITY_OF_DISH_TYPES] = {};
	char input_string[STRING_MAX_SIZE] = {0};
	read_input(input_string);
	write_information_to_dishwasher(input_string, all_dishes);
	dishwasher_interact(all_dishes);
}
