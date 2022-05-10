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
    for(i = 2; i<x-1;i++){
        if((x%i)==0){
            return 0;
        }
    }
    return 1;
}

void *calcPrimes(void *args){
    struct primeRange* aRange = (struct primeRange*)args;
    int x;

    printf("aRange->start = %10d, aRange->end = %d\n",aRange->start,aRange->end);

    // Check every number in Range
    for (x = aRange->start; x < (aRange->end); x++){
        // Prime Algorithn
        int res = primeAlg(x);
        // if(res)
        //     printf("Testing: %d = %d\n", x, res);
   
    }

    printf("Thread done to %10d\n",aRange->end);

    pthread_exit(NULL);
}

// Main
// take max Range and divide in ThreadCount
// Send those Ranges to thread counts
// either print Ranges or return in Array?

int main(){
    // count variables
    int i = 0;

    // specify complete amount of numbers starting from 1
    const int endNumber = 500000;
    const int threadAmount = 10;
    float perThread = (float)endNumber / threadAmount;

    // Range Array
    struct primeRange aRange[threadAmount];
    // thread Array
    pthread_t thread[threadAmount];

    // Initialize Ranges and start threads ???
    for(i = 0; i < threadAmount; i++){
        aRange[i].start = i*perThread+1;
        aRange[i].end = i*perThread+perThread;
        // Set individual ranges
        printf("aRange[%d].start =  %10d\n",i,aRange[i].start);
        printf("aRange[%d].end   =  %10d\n",i,aRange[i].end);
    }

    // force last aRange[] to endNumber
    aRange[threadAmount-1].end = endNumber;
    printf("aRange[%d].end   =  %10d\n",threadAmount-1,aRange[threadAmount-1].end);

    // start threads
    for(i = 0; i < threadAmount; i++){
        pthread_create(&thread[i], NULL, calcPrimes, (void * )&aRange[i]);
    }
    
    // Waiting for threads to end
    for(i = 0; i < threadAmount; i++){
        pthread_join(thread[i],NULL);
    }

    // Starte Thread mit Funktion calcPrimes
    //pthread_create(&thread, NULL, &calcPrimes, &aRange);

    //return value
    //int *retValue;
    //pthread_join(thread,(void**)(&retValue));

    return 0;
}


// TIMES
// endNumber = 500000

// threads   = 1
// time      = 33.69s user 0.26s system 99% cpu 33.957 total

// threads   = 2
// time      = 34.84s user 0.29s system 137% cpu 25.502 total
// time      = 28.29s user 0.00s system 138% cpu 20.451 total

// threads   = 3
// time      =

// threads   = 4
// time      = 29.34s user 0.00s system 242% cpu 12.123 total

//thread     = 10
// time      = 45.81s user 0.03s system 571% cpu 8.023 total

// threads   = 16
// time      = 50.01s user 0.01s system 710% cpu 7.038 total