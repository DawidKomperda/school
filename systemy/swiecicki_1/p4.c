#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    int Liczba, ChildPid, i, Suma;
    FILE *Fd;

    Fd = fopen("tmp.txt", "w+");
    Suma = 0;
    fprintf(Fd, "\n Proces macierzysty pid(%d)  --> Suma=%d", getpid(), Suma);

    if ((ChildPid = fork()) == 0) {
        /* wykonywane przez proces potomny */

        for (i = 0; i < 5; i++) {
            Suma = Suma + 1;
            fprintf(Fd, "\n Proces potomny  pid(%d) --> Suma=%d", getpid(), Suma);
        } // for

        fclose(Fd);
        exit(0); /*zakonczenie procesu potomnego */

    } // if fork ...

    wait(0);
    fprintf(Fd, "\n Proces macierzysty pid(%d)  --> Suma=%d", getpid(), Suma);
    fclose(Fd);
    printf("\n");

    return 0;
}
/* main */