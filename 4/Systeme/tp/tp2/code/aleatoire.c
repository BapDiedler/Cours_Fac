#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 1000000

int* nbValeursTab(int* tab){
    int* val = calloc(sizeof(int),21);
    for(int i=0; i<N; i++){
        val[tab[i]]++;
    }
    return val;
}

int main(int argc, char** argv){

    int* tab = calloc(sizeof(int),N);//init tab de taille N=300
    for(int i=0; i<N; i++){
        tab[i]=rand()%21;
        //printf("%d | ",tab[i]);
    }

    printf("\n\n");

    int * val = nbValeursTab(tab);
    int status;
    pid_t res;
    for(int i=0; i<21; i++){
    //creation de processus enfant
        switch ( res = fork() ){
            case (pid_t) -1 :
                perror("création impossible");fflush(stdout);
                exit(1);
            case (pid_t) 0 :
                /* on est dans le fils */
                printf("%d a %d : %lf \n ",getpid(),i,((float)val[i]/(float)N)*100);fflush(stdout);
                if(val != NULL){
                    free(val);
                }

                if(tab!=NULL){// désallocation mémoire
                    free(tab);
                }
                exit(0);   
        }
    }
    wait(&status);

    if(val != NULL){
        free(val);
    }

    if(tab!=NULL){// désallocation mémoire
        free(tab);
    }

    return EXIT_SUCCESS;
}