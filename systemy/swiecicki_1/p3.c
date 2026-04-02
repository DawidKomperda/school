#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

	int Liczba, ChildPid, i, Suma;

	Suma = 10;

	//printf("\n Proces macierzysty pid(%d)  --> Suma=%d", getpid(), Suma);

	if ((ChildPid = fork()) == 0) {
		/* wykonywane przez proces potomny */

		for (i = 0; i < 5; i++) {
			Suma = Suma + 1;
		} // for

		printf("\n Proces potomny  pid(%d) --> Suma=%d", getpid(), Suma);
		exit(0); /*zakonczenie procesu potomnego */

	} // if fork ...

	wait(0);

	printf("\n Proces macierzysty pid(%d)  --> Suma=%d", getpid(), Suma);

	printf("\n");
}
/* main */
