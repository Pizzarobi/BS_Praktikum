#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

// Dieser Code ist beinahe Identisch zu sem_count.c
// deswegen sind Funktions kommentare in sem_count.c

// Atomare integer
atomic_int count = 0;
atomic_int countInc = 0;

const int MAX_CNT = 100*1000*1000;

void *increment(void *p){
    long inc = (long)p+1;
    printf("Thread inc = %ld\n", inc);
    while(countInc < MAX_CNT){
        // seltener übertretung von countInc von MAX_CNT, da der Vergleich nicht geschützt ist
        if(countInc >= MAX_CNT)
            break;
        // keine Semaphoren notwendig, da atomar
        countInc++;
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

    // starten der threads
    for(long i = 0; i<threadAmount; i++){
        pthread_create(&thread[i], NULL, increment, (void *)(i));
    }

    // warten auf beendigung der threads
    for(int i=0; i<threadAmount; i++){
        pthread_join(thread[i], NULL);
    }

    printf("Every thread done!\n");
    printf("count = %d\n",count);
    printf("countInc = %d\n",countInc);
    printf("MAX_CNT = %d\n",MAX_CNT);

    return 0;
}