#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define NBUFF 10

int nitems; /* tylko do odczytu przez producenta i konsumenta */
struct {    /* wspólne dane producenta i konsumenta */
    int buff[NBUFF];
    sem_t mutex, nempty, nstored;  /* semafory, nie wskaźniki */
} shared;

void *produce(void *), *consume(void *);

int
main(int argc, char **argv)
{
    pthread_t tid_produce, tid_consume;

    if (argc != 2) {
        printf("uzycie:  %s  LiczbaIteracj\n", argv[0]);
        exit(1);
    }
    nitems = atoi(argv[1]);

    /* zainicjowanie trzech semaforów */
    sem_init(&shared.mutex, 0, 1);
    sem_init(&shared.nempty, 0, NBUFF);
    sem_init(&shared.nstored, 0, 0);

    pthread_create(&tid_produce, NULL, produce, NULL);
    pthread_create(&tid_consume, NULL, consume, NULL);

    pthread_join(tid_produce, NULL);
    pthread_join(tid_consume, NULL);

    sem_destroy(&shared.mutex);
    sem_destroy(&shared.nempty);
    sem_destroy(&shared.nstored);
    exit(0);
}

void *
produce(void *arg)
{
    int i;

    for (i = 0; i < nitems; i++) {
        sem_wait(&shared.nempty);   /* oczekiwanie na min. jedno wolne
                                       miejsce w buforze */
        sem_wait(&shared.mutex);
        shared.buff[i % NBUFF] = i; /* zapamietanie w cyklicznym
                                       buforze */
        printf("Producent: Wyprodukowalem element %d do bufora %d\n", i, i % NBUFF);
        sem_post(&shared.mutex);
        sem_post(&shared.nstored);  /* kolejny gotowy element */
    }
    return(NULL);
}

void *
consume(void *arg)
{
    int i;

    for (i = 0; i < nitems; i++) {
        sem_wait(&shared.nstored);  /* oczekiwanie na min. jeden
                                       gotowy element w buforze */
        sem_wait(&shared.mutex);
        if (shared.buff[i % NBUFF] != i)
            printf("Blad bufora! buff[%d] = %d, a spodziewano sie %d\n", i % NBUFF, shared.buff[i % NBUFF], i);
        else
            printf("Konsument: Pobralem element %d z bufora %d\n", shared.buff[i % NBUFF], i % NBUFF);
        sem_post(&shared.mutex);
        sem_post(&shared.nempty);   /* kolejne wolne miejsce */
    }
    return(NULL);
}