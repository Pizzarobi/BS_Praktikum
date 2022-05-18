#include <stdio.h>
#include <pthread.h>

#define TRUE	1
#define FALSE	0

const int max = 1000000;
volatile int count = 0;

volatile int turn = 0;
volatile int flag[2] = { FALSE, FALSE };

void* foo(void*pv)
{
	int myid = (int)pv;
	int other = 1 - myid;
	for( int i = 0; i < max; i++ ) {
		/* Wunsch anmelden */
		flag[myid] = TRUE;
		turn = other;
		/* sicherstellen dass die Variablen gespeichert sind */
//		__asm__ volatile ( "mfence" : : : "memory" );
		/* warten bis der andere fertig ist oder bis ich dran bin */
		while( (flag[other]==TRUE) && (turn == other) ) ;
		count ++;
		flag[myid] = FALSE;

	}
	return 0;
}

int main()
{
	pthread_t t1, t2;

	pthread_create( &t1, NULL, foo, (void*)0 );
	pthread_create( &t2, NULL, foo, (void*)1 );

	pthread_join( t1, NULL );
	pthread_join( t2, NULL );

	printf("Ergebnis: %d\n", count );
	return 0;
}
