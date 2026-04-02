#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main() {

    /* KREOWANIE SEMAFORA W PAMIECI OPERACYJNEJ*/
    sem_t Sem;
    int Wartosc;
    int i;

    Wartosc=10; /*wartosc poczatkowa semafora */

    // Pamiec dla zmiennej Sem musi zostac zaalokowana przed wywolaniem funkcji sem_init

    sem_init(&Sem, 0, Wartosc); /* Drugi parametr funkcji informuje czy semafor ma byc wspoldzielony... */

    sem_getvalue(&Sem, &Wartosc); // pobranie aktualnej wartosci zmiennej semaforowej

    printf("\nWartosc zmiennej semaforowej Sem= %d ", Wartosc);

    for( i=Wartosc; i > 0; i--) {
        sem_wait(&Sem); sem_getvalue(&Sem, &Wartosc);
        printf("\nWartosc zmiennej semaforowej Sem= %d ", Wartosc);

    }// for

    printf("\n");

    sem_destroy(&Sem); // usuniecie semafora

    exit(0);

} // main
