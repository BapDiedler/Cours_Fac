#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/// @brief fonction appelée en cas d'appel du signal SIGINT
/// @param sig 
void sigint(int sig) {
    printf("Au revoir\n");fflush(stdout);
    exit(EXIT_SUCCESS);
}


int main() {

     //création d'un processus
    switch ( fork() ){
        case (pid_t) -1 :
            perror("création impossible");
            exit(EXIT_FAILURE);
        case (pid_t) 0 :
        /* on est dans le fils */

            sleep(5);
            kill(getppid(),SIGINT);

            break;
        default :
        /* on est dans le père*/
        
            signal(SIGINT, sigint);
            sleep(10);
    }

    return EXIT_SUCCESS;
}