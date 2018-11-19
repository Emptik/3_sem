#define DISHWASHER_QUANTITY_OF_DISH_TYPES 8

class dishwasher {
	int wash_time;
	char *dish_type;
	int number_of_dishes;
	void push_wash_time();
	void push_number_of_dishes();
public:
	dishwasher();
	dishwasher(char *array);
	void show_all_values();
	int get_wash_time() { return wash_time; }
	char *get_dish_type() { return dish_type; }
	int get_number_of_dishes() { return number_of_dishes; }
}; 
