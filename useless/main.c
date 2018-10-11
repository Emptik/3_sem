#include <stdlib.h>
#include "prototypes.h"
#include "manager.h"
#include "split.h"
#include "processor.h"

int main(int argc, char *argv[])
{
	char * text = NULL;
	struct command_storage * division = NULL;
	unsigned int time_out = atoi(argv[1]);
	text = read_input();
	division = make_split(text);
	dot_print(division);
	do_all_instructions(division, time_out);
	destroy_storage(division);
	free(text);
	return 0;
}
