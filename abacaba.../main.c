#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

static void generate_string(int latest_letter_number, char * output_string);

int main()
{
	char * string = NULL;
	int latest_letter_number  = 0;
	scanf("%d", & latest_letter_number);
	string = (char*)calloc( 1 << (latest_letter_number + 1), sizeof(char));
	generate_string(latest_letter_number, string);
	printf("%s\n", string);
	free(string);
	return 0;
}

static void generate_string(int latest_letter_number, char * output_string)
{
	if (latest_letter_number > 28 || latest_letter_number < 0) {
		printf("Big number or negative number\n");
		exit(1);
	}
	int current_length = 1;
	int next_symbol = 'a';
	for ( ; latest_letter_number > 0; latest_letter_number--) {
		output_string[current_length / 2] = next_symbol;
		strncpy(output_string + current_length + 1, output_string, current_length);
		current_length *= 2;
		current_length++;
		next_symbol++;
	}
}
