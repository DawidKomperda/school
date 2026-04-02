#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
        pid_t pid;

        printf("Hello\n");
        pid = fork();     /* Not checking for error */
        printf("My PID is %d\n", pid);

	return EXIT_SUCCESS;
}