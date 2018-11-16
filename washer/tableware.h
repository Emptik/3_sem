
//typedef unsigned short int ushort;

class tableware {
	int wash_time;
	char *dish_type;
	int number_of_dishes;
	void push_wash_time();
	void push_number_of_dishes();
public:
	tableware();
	tableware(char * array);
	void pull_all();
};

