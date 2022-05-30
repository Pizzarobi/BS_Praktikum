#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

volatile int count = 0;
volatile int countInc = 0;
const int MAX_CNT = 100*1000*1000;
sem_t sem;

// increment Funktion. Bekommt die ThreadID als Parameter übergeben
void *increment(void *p){
    // casten des void zu einem long
    long inc = (long)p+1;
    printf("Thread inc = %ld\n", inc);
    // inkrementierung von count um jeweils die "ID" des thread+1
    // schützen den kritischen Bereichs mithilfe eines Semaphor
    // sehr unverständliche beschreibung des Ablaufs in Praktikumsanleitung
    // deswegen hier: Anzahl an Inkrementierungen wird durch countInc überprüft
    // Sobald MAX_CNT inkrementierungen stattgefunden haben wird abgebrochen
    while(countInc < MAX_CNT){
        // stoppen falls count schon MAX_CNT entspricht
        // seltene überschreitung von MAX_CNT, da der Vergleich nicht geschützt ist
        if(countInc >= MAX_CNT){
            break;
        }
        sem_wait(&sem);
        countInc++;
        count+=inc;
        sem_post(&sem);
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int threadAmount = 1;

    //Initialisierung des Semaphor
    sem_init(&sem,0,1);

    // Überprüfen und zuordnung der Kommandozeilen Argumente
    if (argc == 2){
        threadAmount = atoi(argv[1]);
    } else{
        printf("Wrong number of Arguments");
        return 0;
    }

    // Initialisierung der threads
    pthread_t thread[threadAmount];

    // starten der threads
    for(long i = 0; i<threadAmount; i++){
        // übergabeparameter ist ein void* cast auf den long i
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