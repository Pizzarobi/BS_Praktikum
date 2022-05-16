#include <stdio.h>
#include <pthread.h>

// Thread-Funktion
void *example_fct(void *args){
    size_t i;
    struct timespec sleep = {0, 1000};

    for(i = 0; i < 100; i++){
        // Schleife, die einen "zufälligen" Buchstaben ausgibt.
        // IDeser wird anhand der Thread ID bestimmt.
        putchar('a' + pthread_self() % 26);
        // Warte kurz; 1 microsekunde
        nanosleep(&sleep, NULL);
    }
    return NULL;
}

int main(){
    // Lege zwei Thread-handle an
    pthread_t threadA, threadB, threadC;
    // Starte zwei Thread mit der auszuführenden Funktion example_fct.
    // Konfiguartions- und Übergabe-Parameter werden nicht gesetzt, daher NULL.
    pthread_create(&threadA, NULL, &example_fct, NULL);
    pthread_create(&threadB, NULL, &example_fct, NULL);
    //pthread_create(&threadC, NULL, &example_fct, NULL);

    // Warte auf Beendigung der beiden Threads
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    //pthread_join(threadC, NULL);

    return 0;
}