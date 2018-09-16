#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
		counter_2 = (counter_2 << 1) + 1;
		ascii += 1;
	}
}
