#include <stdio.h>
#include <pthread.h>

const int max = 1000000;
volatile int count = 0;


void* foo(void*pv)
{
	int myid = (int)pv;
	for( int i = 0; i < max; i++ ) {
		count ++;
	}
	return 0;
}

int main()
{
	pthread_t t1, t2;

	pthread_create( &t1, NULL, foo, 0 );
	pthread_create( &t2, NULL, foo, 1 );

	pthread_join( t1, NULL );
	pthread_join( t2, NULL );

	printf("Ergebnis: %d\n", count );
	return 0;
}
