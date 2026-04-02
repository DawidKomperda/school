#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
        (void) argc;
        
        printf("Here I am: %s's PID is %d\n", argv[0], getpid());

        if (execl("print-pid", "print-pid", (char *)NULL) == -1)
                exit(EXIT_FAILURE);  /* execl failed */

        printf("Here I go: %s's PID is %d\n", argv[0], getpid());

        return EXIT_SUCCESS;
}