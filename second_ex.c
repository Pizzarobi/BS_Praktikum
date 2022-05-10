// Compile Befehl
// g++ -Wall -pthread example.c -o example

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>

struct student{
    char *name;
    size_t len;
};

// Thread-Funktion
void *example_fct(void *args){
    struct student* aStudent = (struct student*)args;
    aStudent->len = strlen(aStudent->name);

    return aStudent;
    // Die Übergabe wird zurück auf einen int-Pointer gecastet
    //uintptr_t *inParam = (uintptr_t *)args;
    // Der Inhalt des Pointers wird ausgegeben
    // printf("Infos von Main: %lu\n", *inParam);
    // return (void*)101010;
}

int main(){
    // Lege ein Thread-Handle, einen Übergabe- und einen Rückgabeparameter an
    pthread_t thread;

    struct student aStudent;
    aStudent.name = "Roberto";
    aStudent.len = 0;

    struct student *bStudent;

    // Starte einen Thread mit der auszuführenden Funktion example_fct
    // Zudem wir einen Parameter übergeben. Konfigurations-parameter werden nicht genutzt daher NULL.
    pthread_create(&thread, NULL, &example_fct, &aStudent);
    //pthread_create(&threadC, NULL, &example_fct, NULL);

    // Warte auf Beendigung der beiden Threads
    pthread_join(thread, (void**)(&bStudent));

    //Inhalt des Rückgabeparameters ausgeben
    printf("Name : %s\n", bStudent->name);
    printf("Laenge: %lu\n",bStudent->len);

    return 0;
}