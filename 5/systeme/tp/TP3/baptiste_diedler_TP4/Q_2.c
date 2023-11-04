#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/**
 * question 1:
 * void* fun_thread(void* arg){
    printf("Bonjour");
    pthread_exit(NULL);
   }
 * 
*/

/// @brief fonction effectuée par les threads
/// @param arg numéro du thread
/// @return NULL pour signaler la fin de la fonction
void* fun_thread(void* arg){
    int id = *(int*)arg;
    printf("Bonjour (%d)\n",id);
    pthread_exit(NULL);
}

int main(void){

    pthread_t tab[10];//tableau contenant les threads
    int id[10];//tableau contenant les ids des threads

    for(int i=0; i<10; i++){//création des threads
        id[i] = i;
        if(pthread_create(&tab[i],NULL,fun_thread,&id[i])){
            perror("une erreur est survenue dans la création d'un thread.\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i<10; i++){//attente de la fin d'excécution des threads
        if(pthread_join(tab[i],NULL)){
            perror("une erreur est survenue dans l'attente d'un thread.\n");
            exit(EXIT_FAILURE);
        }
    }


    return EXIT_SUCCESS;
}