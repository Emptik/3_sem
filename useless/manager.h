struct command_storage *init_storage();
struct instruction_line *init_instruction();
void destroy_storage(struct command_storage *pack);
void destroy_instruction(struct instruction_line *command);
char *read_input();
