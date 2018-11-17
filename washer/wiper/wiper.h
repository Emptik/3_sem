class wiper {
	int wipe_time;
	char *dish_type;
	void push_wipe_time();
public:
	wiper();
	wiper(char *array);
	void show_all_values();
	char *get_dish_type() { return dish_type; }
	int get_wipe_time() { return wipe_time; }
};
