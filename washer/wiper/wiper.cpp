#include <iostream>
#include <cstdlib>
#include <cstring>

#include "wiper.h"
#include "../macro.h"

void read_input(char *input_string);
void write_information_to_wiper(char *dish_information, class wiper all_dishes[]);
void wiper_interact(class wiper *all_dishes);

int main() {
	class wiper all_dishes[WIPER_QUANTITY_OF_DISH_TYPES] = {};
	char input_string[STRING_MAX_SIZE] = {0};
	read_input(input_string);
	write_information_to_wiper(input_string, all_dishes);
	wiper_interact(all_dishes);
}
