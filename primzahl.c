// Compile Befehl
// g++ -Wall -pthread example.c -o example

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>

struct primeRange{
    int start;
    int end;
};

int primeAlg(int x){
    int i;
    for(i = 2; x-1;i++){
        if((x%i)==0){
            return 0;
        }
    }
    return 1;
}

void *calcPrimes(void *args){
    struct primeRange* aRange = (struct primeRange*)args;
    int x;

    // Check every number in Range
    for (x = aRange->start; x<aRange->end;x++){
        // Prime Algorithn
        printf("Testing: %d =", x);
        int res = primeAlg(x);
        printf(" %d\n",res);
    }

    return aRange;
}

// Main
// take max Range and divide in ThreadCount
// Send those Ranges to thread counts
// either print Ranges or return in Array?

int main(){
    pthread_t thread;

    struct primeRange aRange;
    aRange.start = 1;
    aRange.end = 500;

    // Starte Thread mit Funktion calcPrimes
    //pthread_create(&thread, NULL, &calcPrimes, &aRange);

    //return value
    //int *retValue;
    //pthread_join(thread,(void**)(&retValue));


    // TEST CODE VON primeAlg
    printf("3, %d\n",primeAlg(3));
    printf("7, %d\n",primeAlg(7));
    printf("10, %d\n",primeAlg(10));

    return 0;
}