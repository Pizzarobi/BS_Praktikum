// Compile Befehl
// g++ -Wall -pthread example.c -o example

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

volatile int count = 3;
int endNumber = 1000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int primeAlg(int x){
    int i;
    for(i = 2; i<x-1;i++){
        if((x%i)==0){
            return 0;
        }
    }
    return 1;
}

void *calcPrimes(void *p){
    int primeAmount = 0;
    int myNumber = 0;
    while(count < endNumber){
        pthread_mutex_lock(&mutex);
            myNumber = count++;
        pthread_mutex_unlock(&mutex);
        int res = primeAlg(myNumber);
        if(res){
            //printf("%10d , %d,\n",count, res);
            primeAmount++;
        }
    }
    printf("primeAmount = %d\n",primeAmount);
    pthread_exit(NULL);
}

// Main
int main(int argc, char **argv){
    // variables
    int i = 0;
    int threadAmount = 1;

    // Argument handler
    if(argc == 3){
        // set user variables
        endNumber = atoi(argv[1]);
        threadAmount = atoi(argv[2]);
    } else {
        // wrong number of Arguments
        printf("Please specify 2 Arguments.\n");
        printf("For example: %s 10000 6\nEnding program\n",argv[0]);

        return 0;
    }

    // initialize thread Array
    pthread_t thread[threadAmount];

    // start threads
    for(i = 0; i < threadAmount; i++){
        pthread_create(&thread[i], NULL, calcPrimes, NULL);
    }
    
    // Waiting for threads to end
    for(i = 0; i < threadAmount; i++){
        pthread_join(thread[i],NULL);
    }

    printf("Every thread done!\n");
    printf("count = %d, endNumber = %d\n",count,endNumber);
    return 0;
}