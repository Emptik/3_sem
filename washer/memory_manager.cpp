#include <cstdio>
#include <cstdlib> 
#define STRING_MAX_SIZE 100
#define QUANTITY_OF_DISH_TYPES 3

void read_input(char *input_string) {
	int i = -1;
	do {
		i++;
		if (i >= STRING_MAX_SIZE) {
			printf("Too big string\n");
			exit(1);
		}
		input_string[i] = getchar();
	} while (input_string[i] != EOF);
	input_string[i] = '\0';
}
