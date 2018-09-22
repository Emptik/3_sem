#include "prototypes_useless.h"

int main()
{
	char * text = NULL;
	struct List * division = NULL;
	text = load_file();
	assert(text);
	division = split(division, text);
	dot_print(division);
	list_destroy(division);
	free(text);
	return 0;
}
