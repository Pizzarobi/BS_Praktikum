#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

volatile int count = 0;
sem_t sem;

void *foo(){
    for (int i = 0; i < 1000000; i++){
        sem_wait(&sem);
        count++;
        sem_post(&sem);
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t thread[2];

    sem_init(&sem,0,1);

    pthread_create(&thread[0],NULL,foo,NULL);
    pthread_create(&thread[1],NULL,foo,NULL);

    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);

    
    printf("count: %d\n",count);
    return 0;
}