#include <cstring>

class message {
public:
	long type;
	char dish[10];
	int fd;
	message() {
		type = 0; 
		fd = 0;
	}
	message(char *array) {
		type = 1;
		strcpy(dish, array);
		fd = 0;
	}
	char *get_dish() { return dish; }
};
