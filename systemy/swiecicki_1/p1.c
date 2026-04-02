#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

	int Liczba;
	int ChildPid;
	int i;

	if ((ChildPid = fork()) == 0) {
		/* wykonywane przez proces potomny */

		sleep(2);
		for (i = 0; i < 5; i++) {
			printf("\n Proces potomny pid(%d), i=%d", getpid(), i);
			sleep(2);
		} /* for */

		printf("\n Proces potomny pid(%d) --> operacja zakonczonie", getpid());
		exit(0); /*zakonczenie procesu potomnego */

	} /* if fork ... */

	printf("\n Proces macierzysty pid(%d)"
		   "\n ---> Czekam na zakonczenie procesu potomnego pid(%d)", getpid(), ChildPid);

	wait(0);

	printf("\n Proces macierzysty pid(%d)"
		   "\n ---> Proces potomny zostal zakonczony pid(%d)", getpid(), ChildPid);

	printf("\n");
}
/* main */
