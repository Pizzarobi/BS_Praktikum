#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

volatile int count = 0;
const size_t MAX_CNT = 1000000;
sem_t sem;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* incSEM(void* p){
    for (int i = 0; i < (int)MAX_CNT; i++){
        sem_wait(&sem);
        count++;
        sem_post(&sem);
    }

    pthread_exit(NULL);
}

void* decSEM(void* p){
    for (int i = 0; i < (int)MAX_CNT; i++){
        sem_wait(&sem);
        count--;
        sem_post(&sem);
    }

    pthread_exit(NULL);
}

void* incMUT(void* p){
    for(int i = 0; i < (int)MAX_CNT; i++){
        pthread_mutex_lock(&mutex);
        count++;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* decMUT(void* p){
    for(int i = 0; i < (int)MAX_CNT; i++){
        pthread_mutex_lock(&mutex);
        count--;
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void* incDMUT(void* p){
    for(int i = 0; i < (int)MAX_CNT; i++){
        pthread_mutex_lock((pthread_mutex_t*)p);
        count++;
        pthread_mutex_unlock((pthread_mutex_t*)p);
    }
    pthread_exit(NULL);
}

void* decDMUT(void* p){
    for(int i = 0; i < (int)MAX_CNT; i++){
        pthread_mutex_lock((pthread_mutex_t*)p);
        count--;
        pthread_mutex_unlock((pthread_mutex_t*)p);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t thread[2];
    
    sem_init(&sem,0,1);

    // Initialize Dynamic Mutex
    pthread_mutex_t dynMutex;
    pthread_mutex_init(&dynMutex, NULL);

    pthread_create(&thread[0],NULL,incMUT,NULL);
    pthread_create(&thread[1],NULL,decMUT,NULL);

    // Dynamic Mutex call
    // pthread_create(&thread[0],NULL,incDMUT,&dynMutex);
    // pthread_create(&thread[1],NULL,decDMUT,&dynMutex);

    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);

    pthread_mutex_destroy(&mutex);

    
    printf("count: %d\n",count);
    return 0;
}