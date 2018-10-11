struct command_storage {
	size_t number_of_commands;
	struct instruction_line ** lines;
};

struct instruction_line {
	size_t response_time;
	char * instruction;
};
