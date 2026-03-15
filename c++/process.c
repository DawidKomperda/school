#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int fork(void);
extern int getpid(void);

int main(){
    int Liczba, Child, i, Suma;
    FILE * fd;

    fd = fopen("tmp.txt", "w+");
    Suma = 0;
    fprintf(fd, "\n Proces macierzysty pid(%d) ->>. Suma=%d", getpid(), Suma);
    fflush(fd); 

    if((Child = fork())  == 0){
        // Potomny
        fprintf(fd, "\n Process potomny (pid: %d) oblicza wektor:\n", getpid());
        int vector[5];
        int computed_sum = 0;
        for (int j = 0; j < 5; j++) {
            vector[j] = j * 2;
            computed_sum += vector[j];
            fprintf(fd, " v[%d] = %d", j, vector[j]);
        }
        
        FILE * temp = fopen("temp.txt", "w");
        fprintf(temp, "%d", computed_sum);
        fclose(temp);
        
        fprintf(fd, "\n");
        fclose(fd);
        
        // Return from main instead of using exit() from <stdlib.h>
        return 0;
    }
    
    wait(NULL);
    
    FILE * temp_in = fopen("temp.txt", "r");
    if(temp_in != NULL) {
        fscanf(temp_in, "%d", &Suma);
        fclose(temp_in);
    }
    // Write to console
    printf("\n process macierzysty pid(%d) ->> Suma =%d\n", getpid(), Suma);
    
    fclose(fd);
    return 0;


}