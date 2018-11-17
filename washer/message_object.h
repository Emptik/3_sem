class message {
public:
	long type;
	char *dish;
	int fd;
	message() {
		type = 0; 
		dish = 0;
		fd = 0;
	}
	message(char *array) {
		type = 1;
		dish = array;
		fd = 0;
	}
	char *get_dish() { return dish; }
};
