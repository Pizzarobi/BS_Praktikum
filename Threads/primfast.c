// Compile Befehl
// g++ -Wall -pthread example.c -o example

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

struct primeRange{
    int start;
    int interval;
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
    for (x = aRange->start; x < (aRange->end); x+=aRange->interval){
        // Prime Algorithm
        int res = primeAlg(x);
        if(res)
            printf("Testing: %d = %d\n", x, res);
    }

    printf("Thread done: %10d\n",aRange->interval);
    pthread_exit(NULL);
}

// Main
// take max Range and divide in ThreadCount
// Send those Ranges to thread counts
int main(int argc, char **argv){
    // variables
    int i = 0;
    int endNumber = 1000;
    int threadAmount = 1;

    // Argument handler
    if(argc < 3){
        // wrong number of Arguments
        printf("Please specify 2 Arguments.\n");
        printf("For example: %s 10000 6\nEnding program",argv[0]);

        return 0;
    }else if(argc == 3){
        // set user variables
        endNumber = atoi(argv[1]);
        threadAmount = atoi(argv[2]);
    }

    // specify complete amount of numbers starting from 1
    float perThread = (float)endNumber / threadAmount;

    // initialize range and thread Array
    struct primeRange aRange[threadAmount];
    pthread_t thread[threadAmount];

    // Set ranges
    for(i = 0; i < threadAmount; i++){
        // Set individual ranges
        aRange[i].start = i+1;
        aRange[i].interval = threadAmount;
        aRange[i].end = endNumber;

        //printf("aRange[%d].start =  %10d\n",i,aRange[i].start);
        //printf("aRange[%d].end   =  %10d\n",i,aRange[i].end);
    }
    // force last aRange[] to endNumber
    // aRange[threadAmount-1].end = endNumber;

    // start threads
    // for(i = 0; i < threadAmount; i++){
    //     pthread_create(&thread[i], NULL, calcPrimes, (void * )&aRange[i]);
    // }
    
    // Waiting for threads to end
    // for(i = 0; i < threadAmount; i++){
    //     pthread_join(thread[i],NULL);
    // }

    pthread_create(&thread[3], NULL, calcPrimes, (void *)&aRange[3]);

    pthread_join(thread[3],NULL);

    printf("Every thread done!\n");
    return 0;
}