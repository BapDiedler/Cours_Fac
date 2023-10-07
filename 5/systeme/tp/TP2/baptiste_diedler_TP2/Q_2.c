#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    pid_t res;
    res = fork();
    printf("%d: Bonjour\n",getpid());fflush(stdout);
    //création d'un processus
    switch ( res ){
        case (pid_t) -1 :
            perror("création impossible");
            exit(1);
        case (pid_t) 0 :
        /* on est dans le fils */
            sleep(2);
            break;
        default :
        /* on est dans le père*/
            sleep(5);
    }


    printf("%d: AU revoir\n",getpid());fflush(stdout);
            

    return EXIT_SUCCESS;
}