#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static void * DoIt(void *arg);

int main() {

    pthread_t tid;

    printf("\nWatek macierzysty tid(%ld):", pthread_self());
    pthread_create(&tid, NULL, &DoIt, NULL);
    printf("\nWatek potomny zostal utworzony tid(%ld)", tid);

    pthread_join(tid, NULL);

    printf("\nWatek macierzysty tid(%ld)->Watek potomny zakończony tid(%ld)",
            pthread_self(), tid);

    printf("\n");
    return 0;
}

static void * DoIt(void *arg) {
    int i;
    for (i = 0; i < 5; i++) {
        printf("\n Watek potomny tid(%ld), i=%d", pthread_self(), i);
        sleep(2);
    } // for

    printf("\nWatek potomny tid(%ld) --> operacja zakonczenie", pthread_self());
    return NULL;
}
