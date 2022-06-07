#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <inttypes.h>
#include <stdatomic.h>
#include <time.h>
#include "linked_list.h"

#define MAX_LIST 10

node_t* list = NULL;
pthread_t t1,t2, print;
pthread_mutex_t mutex;
pthread_cond_t data_in = PTHREAD_COND_INITIALIZER;
pthread_cond_t data_out = PTHREAD_COND_INITIALIZER;
int data_in_list = 0;

int primeAlg(int x){
    printf("Prim: %d\n",x);
    int i;
    for(i = 2; i<x-1;i++){
        if((x%i)==0){
            return 0;
        }
    }
    return 1;
}

void delay(int time)
{
    printf("Delay: %d\n",time);
    int a = 0;
    for(int i = 0 ; i < time; i++)
    {
        a++;
    };
}

void* producer()
{
    pthread_mutex_lock(&mutex);

    srand(time(NULL));
    while(data_in_list >= MAX_LIST){
        pthread_cond_wait(&data_out, &mutex);
    } 
    pthread_cond_signal(&data_in);
    delay(rand());
    list_insert_front(&list, rand());
    
    data_in_list++;

    pthread_mutex_unlock(&mutex);
}

void* consumer()
{
    pthread_mutex_lock(&mutex);
    srand(time(NULL));
    while(data_in_list <= 0){
        pthread_cond_wait(&data_in, &mutex);
    }
    pthread_cond_signal(&data_out);
    primeAlg(list_get_tail(list));
    list_remove_tail(list);
    data_in_list--;

    pthread_cond_signal(&data_out);
    pthread_mutex_unlock(&mutex);
}

int main()
{
    srand(time(NULL));
    list = list_create_node(0);
    for(int i = 0; i < MAX_LIST-1; i++){
            list_insert_front(&list, rand());
            data_in_list++;
    }

    pthread_mutex_init(&mutex, NULL);

   for(int i = 0; i < MAX_LIST; i++)
   {
	    pthread_create(&t1, NULL, producer, NULL);
        pthread_create(&t2, NULL, consumer, NULL);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
   }

    list_free(&list);

    pthread_mutex_destroy(&mutex);

    return 0;
}