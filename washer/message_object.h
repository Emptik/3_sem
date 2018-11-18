#include <cstring>

class message {
	long type;
	char dish[MAX_TYPE_SIZE];
public:
	message() {
		type = 0;
		dish[MAX_TYPE_SIZE] = {0};
	}
	message(char *array) {
		type = 1;
		strcpy(dish, array);
	}
	char *get_dish() { return dish; }
};
