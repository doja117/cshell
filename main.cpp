#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <sys/wait.h> 

int main() {
    char cumm[1024]; 
    
    while (1) {

        write(1, "$ ", 2);

  
        memset(cumm, 0, sizeof(cumm));

   
        ssize_t bytes_read = read(0, cumm, sizeof(cumm) - 1);
        if (bytes_read < 0) {
            perror("Error reading input");
            continue;
        }


        cumm[bytes_read - 1] = '\0'; 

     
        const pid_t p = fork();
        if (p == 0) {
          
            char* args[10];
            int i = 0;
            char* token = strtok(cumm, " ");
            while (token != NULL && i < 9) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL; 

            execvp(args[0], args);

            perror("Error executing command");
            exit(EXIT_FAILURE);
        } else if (p > 0) {
            int status;
            waitpid(p, &status, 0);
        } else {
            perror("Fork failed");
        }
    }

    return 0;
}
