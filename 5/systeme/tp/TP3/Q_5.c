#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NB_THREADS 4

volatile int lecteur_count = 0;

sem_t lecture_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t base_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t ecriture_lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * C1: Plusieurs lecteurs peuvent accéder à la base en lecture en même temps.
 * C2: Un seul écrivain peut accéder à la base à la fois.
 * C3: Un écrivain ne peut pas accéder à la base en même temps que des lecteur.
*/

/**Pour la question 2 je vais impléméneter deux sémaphores pour régler le problème donné.
 * Le premier permet de regler le problème avec la lecture
 * Le deuxième permet de regler le problème avec l'écriture
*/


//FONCTION DONNEES SUR LE SUJET
void lire(){//fonction de lecture
    pthread_mutex_lock(&base_lock);
    pthread_mutex_lock(&lecture_lock);
    if(lecteur_count == 0)
        pthread_mutex_lock(&ecriture_lock);
    pthread_mutex_unlock(&base_lock);
    lecteur_count++;
    pthread_mutex_unlock(&lecture_lock);

    printf("Lecture début\n");
    usleep(rand() % 500000);
    printf("Lecture fin\n");

    pthread_mutex_lock(&lecture_lock);
    lecteur_count--;
    if (lecteur_count == 0)
        pthread_mutex_unlock(&ecriture_lock);
    pthread_mutex_unlock(&lecture_lock);
}
void ecrire(){//fonction d'écriture
    pthread_mutex_lock(&base_lock);
    pthread_mutex_lock(&ecriture_lock);
    pthread_mutex_unlock(&base_lock);

    printf("Écriture début\n");
    usleep(rand() % 500000);
    printf("Écriture fin\n");

    pthread_mutex_unlock(&ecriture_lock);
}

void* run(void* arg){//fonction qui simule aléatoirement la lecture ou l'écriture
    while(1)
        rand()%2==0 ? lire() : ecrire();
}


int main(void){

    pthread_t tab[NB_THREADS];

    for(int i=0; i<NB_THREADS; i++){//création des threads
        if(pthread_create(&tab[i], NULL, run, NULL)){
            perror("une erreur est survenue dans la création d'un thread.\n");
            exit(EXIT_FAILURE);
        }
    }

/*
    for(int i=0; i<NB_THREADS; i++){//attente des threads. Mais ne sert à rien car on a une boucle infinie
        if(pthread_join(tab[i], NULL)){
            perror("une erreur est survenue dans l'attente d'un thread.\n");
            exit(EXIT_FAILURE);
        }
    }
*/

    return EXIT_SUCCESS;
}

/**
 * Question 1:
 * On se rend compte que avec simplement deux threads, la condition C3 n'est pas respecté.(lire début \n ecrire début)
 * Par contre, la conditon C1 est respecté car (lire début \n lire début) se trouve à la suite.
 * C'est que au moins deux threads étaient en train de lire en même temps.
 * Et la C2 nest pas non plus respecté car (ecrire début \n ecrire début) se qui montre bien que deux écrivains peuvent acéder à la base en même temps.
 * 
 
 void lire(){//fonction de lecture
    pthread_mutex_lock(&mutex);
    printf("lire début\n");
    usleep(rand()%500000);
    printf("lire fin\n");
    pthread_mutex_unlock(&mutex);
}
 void ecrire(){//fonction d'écriture
    pthread_mutex_lock(&mutex);
    printf("ecrire début\n");
    usleep(rand()%500000);
    printf("ecrire fin\n");
    pthread_mutex_unlock(&mutex);
}

 * 
 * Question 2:
 * Pour resoudre le problème, on va implémenter le principe des sémaphores.
 * Mais si l'on veut résoudre le problème de la famine il faudrait implémenter une file pour re présenter l'ordre de passage des threads à la ressource.
*/