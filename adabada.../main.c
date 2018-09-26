#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// FIXIT: стилевые замечания
// 1) пробелы вокруг бинарных операторов (n+1) -> (n + 1)
// 2) нет пробелы перед запятой: (n , string) -> (n, string)
// 3) именование переменных: counter_1, counter_2, ascii ... неясно их предназначение ... возможно хватит одного с названием, например
// currentStringLength или currentStringHalfLength ... и вместо ascii, например, nextSymbol
// Крутость кода в том числе измеряется тем, сколько надо времени новому человеку, чтобы с ним разобраться.

void GenerateString(int n, char * s);

int main()
{
	char * string = NULL;
	int n = 0;
	scanf("%d", &n);
	string = (char*)calloc( 1 << (n+1), sizeof(char));
	GenerateString(n , string);
	printf("%s\n", string);
	free(string);
	return 0;
}

void GenerateString(int n, char * s)
{
	assert(n < 28 && n > 0);
	int counter_1 = 0;
	int ascii = 'b';
	int counter_2 = 1;
	s[counter_1] = 'a';
	counter_1++;
	for( ; n > 0; n--)
	{
		strncpy(s + counter_1 * 2, s, counter_2);
		s[counter_2] = ascii;
		counter_1 *= 2;
		// Современные компиляторы в режиме release (компиляция с ключом -O2 или -O3 для gcc) сгенерит одинаковый ассемблерный код
		// и для *2 и для << 1. Т.е. здесь лучше отдать предпочтение читаемости кода и выбрать вариант * 2.
		counter_2 = (counter_2 << 1) + 1;
		ascii += 1;
	}
}
