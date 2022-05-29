#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>

atomic_int count = 0;
const int MAX_CNT = 100*1000*1000;

void *increment(void *p){
    long inc = (long)p;
    printf("Thread inc = %ld\n", inc);
    while(count < MAX_CNT){
        count+=inc;
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int threadAmount = 1;

    if (argc == 2){
        threadAmount = atoi(argv[1]);
    } else{
        printf("Wrong number of Arguments");
        return 0;
    }

    pthread_t thread[threadAmount];

    // start threads
    for(long i = 0; i<threadAmount; i++){
        pthread_create(&thread[i], NULL, increment, (void *)(i+1));
    }

    // Waiting for threads to end
    for(int i=0; i<threadAmount; i++){
        pthread_join(thread[i], NULL);
    }

    printf("Every thread done!\n");
    printf("count = %d\n",count);
    printf("MAX_CNT = %d\n",MAX_CNT);

    return 0;
}