#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define TAILLE_TABLEAU 1000 // dimension du tableau
int* tab;//déclaration du tableau en variable globale

void* fun_thread(void* pos){

    int debut = *(int*)pos==0 ? 0 : TAILLE_TABLEAU/2;
    int fin = *(int*)pos==0 ? TAILLE_TABLEAU/2 : TAILLE_TABLEAU;
    
    for(int i=debut; i<fin; i++){//recherche d'occurence
        //usleep(10000);
        if(tab[i]==0)
            printf("indice(%d)\n",i);
    }
    pthread_exit(NULL);
}

/// @brief fonction recherche_tab permet de rechercher les 0 dans un tableau d'entier
void recherche_tab(){
    pthread_t thread1;
    pthread_t thread2;
    int id1 = 0;//variable pour la case de départ du thread
    int id2 = 1;

    //création des threads
    if(pthread_create(&thread1, NULL, fun_thread, &id1)){
        perror("une erreur est survenue dans la création du premier thread.\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&thread2, NULL, fun_thread, &id2)){
        perror("une erreur est survenue dans la création du deuxième thread.\n");
        exit(EXIT_FAILURE);
    }

    //attente des threads
    if(pthread_join(thread1,NULL)){
            perror("une erreur est survenue dans l'attente d'un thread.\n");
            exit(EXIT_FAILURE);
    }
    if(pthread_join(thread2,NULL)){
            perror("une erreur est survenue dans l'attente d'un thread.\n");
            exit(EXIT_FAILURE);
    }
}

/// @brief fonction 2 de l'exo 4
void question1(){

    tab = (int*)calloc(sizeof(int),TAILLE_TABLEAU);//déclaration tableau d'entier de taille TAILLE_TABLEAU

    srand(time(NULL));
    for(int i=0; i<TAILLE_TABLEAU; i++)//initialisation aléatoire du tableau
        tab[i]=rand()%100;
    
    recherche_tab();
}

///@brief fonction main contenant les tests pour répondre à la question 1 et 2
int main(int argc, char** argv){

    clock_t temps_depart, temps_arrivee;
    double temps_ecoule1;

    printf("\tquestion1 :\n");
    temps_depart = clock();//test du premier programme
    question1();
    temps_arrivee = clock();
    temps_ecoule1 = (double)(temps_arrivee - temps_depart) / CLOCKS_PER_SEC;

    printf("(*Le temps écoulé est de %f secondes.*)\n", temps_ecoule1);

    return EXIT_SUCCESS;
}