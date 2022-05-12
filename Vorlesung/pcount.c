#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

volatile int count = 0;

void *foo(void* pv){
    int myID = (int)pv;
    for (int i = 0; i < 1000000; i++){
        count++;
    }

    pthread_exit(NULL);
}

int main(){
    pthread_t thread[2];

    pthread_create(&thread[0],NULL,foo,NULL);
    pthread_create(&thread[1],NULL,foo,NULL);

    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);

    printf("count: %d\n",count);
    return 0;
}