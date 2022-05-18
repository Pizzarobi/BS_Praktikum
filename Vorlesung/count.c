#include <stdio.h>

const int max = 1000000;
volatile int count = 0;

void foo(void)
{
	for( int i = 0; i < max; i++ )
		count ++;
}

int main()
{
	foo();

	printf("Ergebnis: %d\n", count );
	return 0;
}
