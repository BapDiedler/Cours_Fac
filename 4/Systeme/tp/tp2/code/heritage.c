#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    pid_t res;
    int tab[4] = {1,1,1,1};
    int status;
    //création d'un processus
    switch ( res = fork() ){
        case (pid_t) -1 :
            perror("création impossible");fflush(stdout);
            exit(1);
        case (pid_t) 0 :
        /* on est dans le fils */
            printf("le fils est %d\n",getpid());fflush(stdout);
            for(int i=0; i<4; i++){
                printf("%d | ",tab[i]);fflush(stdout);
                tab[i] = 4;
            }
            printf("\n");
            sleep(2);
            printf("adresse du tableau %p\n",tab);
            for(int i=0; i<4; i++){
                printf("%d | ",tab[i]);fflush(stdout);
            }
            printf("\n");
            break;
        default :
        /* on est dans le père*/
            printf("creation du premier processus : %d\n",getpid());fflush(stdout);
            for(int i=0; i<4; i++){
                printf("%d | ",tab[i]);fflush(stdout);
                tab[i]++;
            }
            printf("\n");
            wait(&status);
            printf("adresse du tableau %p\n",tab);
            for(int i=0; i<4; i++){
                printf("%d | ",tab[i]);fflush(stdout);
            }
            printf("\n");
    }
    return 0;
}