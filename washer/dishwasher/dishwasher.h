class dishwasher {
	int wash_time;
	char *dish_type;
	int number_of_dishes;
	void push_wash_time();
	void push_number_of_dishes();
public:
	dishwasher();
	dishwasher(char *array);
	void show_values();
}; 
