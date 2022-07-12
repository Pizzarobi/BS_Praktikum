#include "list.h"
#include "pthread.h"
#include "time.h"
#include <stdbool.h>

#define erz 2
#define ver 3
#define wdh 50

void *erzfunc(void *uebergabe);
void *verfunc(void *uebergabe);
void istprimzahl(int temp);


// Struktur zur Übergabe an die Thread-Funktion
struct uebergabe
{
    node_t *mylist;
};

struct uebergabe liste;
node_t *mylist;
extern sem_t semaphore1;
extern sem_t countsem;
node_t *primzahlarray;

sem_t elemente;
int elemvalue;

// ---------------------------------------------
// Benötigt für Primzahlberechnung
// ---------------------------------------------
void istprimzahl(int temp);

sem_t sem;
sem_t erh;
int maxprimzahl;
int wo;
int wieviele;

// ------------------------------------------------------------
// ------------------------------------------------------------
//                      MAIN-FUNKTION
// ------------------------------------------------------------
// ------------------------------------------------------------

int main()
{
    // Threads deklarieren
    pthread_t erzeuger[erz];
    pthread_t verbraucher[ver];

    srand(time(NULL));
    liste.mylist = mylist;

    // Semaphoren für Thread initialisieren
    sem_init(&semaphore1, 0, 1); // Schutzsemaphore -> Schützt vor gleichzeitigem Zugriff
    sem_init(&countsem, 0, 0);   // Zählsemaphore -> Haben wir ein Element in der Liste

    // Semaphoren für Primzahlberechnung initialisieren
    sem_init(&sem, 0, 1);
    sem_init(&erh, 0, 1);

    sem_init(&elemente, 0, erz*wdh);

    // ----------------------------
    // Threads starten
    // ----------------------------
    // Erzeuger-Threads:
    for (int i = 0; i < erz; i++)
    {
        pthread_create(&erzeuger[i], NULL, &erzfunc, (void *)&liste);
    }
    // Verbraucher-Threads
    for (int j = 0; j < ver; j++)
    {
        pthread_create(&verbraucher[j], NULL, &verfunc, (void *)&liste);
    }

    // ---------------------------
    // Threads beenden
    // ---------------------------
    for (int i = 0; i < erz; i++)
    {
        pthread_join(erzeuger[i], NULL);
    }
    for (int j = 0; j < ver; j++)
    {

        pthread_join(verbraucher[j], NULL);
    }

    // Liste ausgeben
    printf("\n\n\n");
    printlist(liste.mylist);
    printlist(primzahlarray);
    printf("\nWir haben %d Primzahlen.\n", wieviele);

    return EXIT_SUCCESS;
}

void *erzfunc(void *uebergabe)
{
    struct uebergabe *u1 = (struct uebergabe *)uebergabe;
    for (int i = 0; i < wdh; i++)
    {
        sem_wait(&semaphore1);
        u1->mylist = list_insert_end(u1->mylist, rand());
        sem_post(&countsem);
        sem_post(&semaphore1);
    }
    return NULL;
}

void *verfunc(void *uebergabe)
{
    do
    {
        sem_wait(&elemente);
        sem_wait(&countsem);
        sem_getvalue(&elemente, &elemvalue);
        printf("So viele gibts noch: %d\n", elemvalue);
        sem_wait(&semaphore1);
        struct uebergabe *u1 = (struct uebergabe *)uebergabe;
        int data = list_get_head(u1->mylist);
        u1->mylist = list_remove_head(u1->mylist);
        sem_post(&semaphore1);
        printf("Data: %d\n", data);
        istprimzahl(data);
        sem_getvalue(&elemente, &elemvalue);
        if(elemvalue <= 0)
        {return NULL;}
    } while ((sem_getvalue(&elemente, &elemvalue) == 0));
    return NULL;
}

void istprimzahl(int temp)
{
    int status = 0;
    int i = 2;
    while (i < temp)
    {
        if (temp % i == 0)
        {
            status = 1;
            break;
        }
        i++;
    }
    if (status == 0)
    {
        sem_wait(&erh);
        primzahlarray = list_insert_end(primzahlarray, temp);
        wieviele++;
        sem_post(&erh);
    }
}
