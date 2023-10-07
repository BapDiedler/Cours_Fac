#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile int cpt = 0;//variable globale à incrémenter
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/// @brief fonction excécuté par les threads
/// @param var variable NULL
/// @return NULL pour signaler la fin du thread
void* fun_thread(void* var){

    for(int i=0; i<10000; i++){
        pthread_mutex_lock(&mutex);//lock les interruptions
        cpt++;
        pthread_mutex_unlock(&mutex);//unlock les interruptions
    }

    pthread_exit(NULL);
}


int main(void){

    pthread_t tab[10];//tableau de thread

    //initialisation des threads
    for(int i=0; i<10; i++){
        if(pthread_create(&tab[i],NULL,fun_thread, NULL)){
            perror("une erreur est survenue dans la création d'un thread.\n");
            exit(EXIT_FAILURE);
        }
    }

    //attente des threads
    for(int i=0; i<10; i++){
        if(pthread_join(tab[i],NULL)){
            perror("une erreur est survenue dans l'attente d'un thread.\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("le compteur vaut maintenant %d\n",cpt);

    return EXIT_SUCCESS;
}