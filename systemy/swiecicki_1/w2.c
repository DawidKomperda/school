#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static void * DoIt(void *arg);

int Suma;

int main() {

    pthread_t tid;

    Suma = 10;
    printf("\nWatek macierzysty tid(%ld) Suma=%d", pthread_self(), Suma);
    pthread_create(&tid, NULL, &DoIt, NULL);
    printf("\nWatek potomny zostal utworzony tid(%ld)", tid);

    pthread_join(tid, NULL);
    printf("\nWatek macierzysty tid(%ld)->Watek potomny zakończony tid(%ld) Suma=%d",
            pthread_self(), tid, Suma);

    printf("\n");
    return 0;
}

static void * DoIt(void *arg) {
    int i;
    for (i = 0; i < 5; i++) {
        Suma = Suma + 1;
        printf("\n Watek potomny tid(%ld), i=%d, Suma=%d", pthread_self(), i, Suma);
        sleep(2);
    } // for

    printf("\nWatek potomny tid(%ld) --> operacja zakonczenie", pthread_self());
    return NULL;
}
