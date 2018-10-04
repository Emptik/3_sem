#include "prototypes.h"

int main(int argc, char *argv[])
{
	char * text = NULL;
	struct command_storage * division = NULL;
	time_out = atoi(argv[1]);
	text = fill_arr();
	assert(text);
	division = make_split(text);
	dot_print(division);
	work(division);
	destroy_storage(division);
	free(text);
	return 0;
}
