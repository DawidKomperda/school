#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void print_chars(char *s)
{
        for ( ; *s != '\0'; putchar(*s++)) ;
}

int main()
{
        pid_t pid;
        setbuf(stdout, NULL);  /* Want unbuffered output */

        if ( (pid = fork()) < 0 )
                fprintf(stderr, "Can't create fork.");
        else if (pid == 0)
                print_chars("Child says:  \"Hello there!\"\n");
        else
                print_chars("Parent says:  \"Is anyone home?\"\n");

        return EXIT_SUCCESS;
}