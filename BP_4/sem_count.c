#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

volatile int count = 0;
const int MAX_CNT = 100*1000*1000;
sem_t sem;

void *increment(void *p){
    long inc = (long)p;
    printf("Thread inc = %ld\n", inc);
    while(count < MAX_CNT){
        sem_wait(&sem);
        count+=inc;
        sem_post(&sem);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    uint8_t threadAmount = 1;

    sem_init(&sem,0,1);

    if (argc == 2){
        threadAmount = atoi(argv[1]);
    } else{
        printf("Wrong number of Arguments");
        return 0;
    }

    pthread_t thread[threadAmount];

    // start Threads
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