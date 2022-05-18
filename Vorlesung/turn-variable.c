#include <stdio.h>

volatile int count = 0;
volatile int flag = 0;


void foo() {

	for( int i=0; i< 1000000; i++ ) {
		while( flag > 0 ) ;
		flag = 1;
		count = count + 1;
		flag = 0;
	}
}

int main()
{
	foo();
	foo();

	printf("count = %d\n", count );
	return 0;
}
