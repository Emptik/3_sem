#include <cstdio>
#include <cstdlib> 
#include <iostream>

#include "macro.h"

void read_input(char *input_string) {
	int i = -1;
	do {
		i++;
		if (i >= STRING_MAX_SIZE) {
			cout << "Too big string" << endl;
			exit(11);
		}
		input_string[i] = getchar();
	} while (input_string[i] != EOF);
	input_string[i] = '\0';
}
