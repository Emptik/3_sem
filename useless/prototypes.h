#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/signal.h>

#define STRING_MAX_SIZE 5000
#define MAX_NUMBER_OF_ARGUMENTS 100

struct command_storage {
	size_t number_of_commands;
	struct instruction_line ** lines;
};

struct instruction_line {
	size_t response_time;
	char * instruction;
};

// FIXIT: я забыл сказать на семинаре, но использовать глобальные переменные стоит только в том случае, если без нее прям совсем никак.
// Сейчас точно не тот случай.
int time_out;

// Идея разделить реализации ф-й по разным *.c файлам - очень хорошая. Но
// 1) Можно было бы разделить и заголовочный файл на части: ...manager.h, ...processor.h, constants.h и т.п.
// 2) Фактически вам не нужны никакие include'ы здесь. Правильно наоборот в заголовочном файле писать минимум includ'ов.
// Это значительно влияет на время компиляции в крупных проектах. Если напомните, я на семинаре детальнее расскажу.
struct command_storage *init_storage();
struct instruction_line *init_instruction();
void destroy_storage(struct command_storage *pack);
void destroy_instruction(struct instruction_line *command);

// Как думаете, что подумает незнакомый с кодом человек при виде ф-и с названием fill_arr?
// Я удивился, например, т.к. кажется, что в fill мы должны передать параметром указатель на массив какой-то ...
// На самом деле у вас внутри что-то вроде read_input или read_input_as_string
char *fill_arr();

// возможно make_split больше похож на parse, т.к. вы не просто бьете на слова, но еще что-то интерпретируете как числа
struct command_storage *make_split(char *array_data);
void dot_print(struct command_storage * strings);

// work видимо это что-то вроде do_all_instructions
void work(struct command_storage * my_struct);
void do_instruction(struct instruction_line * command);
void kill_process(size_t *pid, size_t instruction_time);

// На самом деле в заголовочном файле должно быть только то, что будет использоваться "пользователями".
// Например, kill_process вызывается только внутри work, поэтому выносить её в заголовочный файл не надо, чтобы не
// нагружать "пользователя" детялями реализации
