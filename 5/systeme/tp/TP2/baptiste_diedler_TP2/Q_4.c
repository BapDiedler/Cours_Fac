#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define N 1000 // dimension du tableau

/// @brief fonction 1 de l'exo 4
void question1(){

    int* tab = (int*)calloc(N,sizeof(int));//déclaration tableau d'entier de taille N

    srand(time(NULL));//initialisation aléatoire des variables du tableau
    for(int i=0; i<N; i++)
        tab[i]=rand()%100;

    for(int i=0; i<N; i++){//recherche d'occurance de 0
        //usleep(10000);
        if(tab[i]==0){
            printf("indice(%d)\n",i);fflush(stdout);
        }
    }

    free(tab);
}

/// @brief fonction 2 de l'exo 4
void question2(){

    int status;
    int* tab = (int*)calloc(N,sizeof(int));//déclaration tableau d'entier de taille N
    srand(time(NULL));

    for(int i=0; i<N; i++)//initialisation
        tab[i]=rand()%100;

    //création d'un processus
    switch ( fork() ){
        case (pid_t) -1 :
            perror("création impossible");
            exit(EXIT_FAILURE);
        case (pid_t) 0 :
        /* on est dans le fils */

            for(int i=0; i<N/2; i++){//recherche d'occurence
                //usleep(10000);
                if(tab[i]==0){
                    printf("indice(%d)\n",i);fflush(stdout);
                }
            }
	     exit(0);
            break;
        default :
        /* on est dans le père*/

            for(int i=N/2; i<N; i++){//recherche d'occurence
                //usleep(10000);
                if(tab[i]==0){
                    printf("indice(%d)\n",i);fflush(stdout);
                }
            }
            wait(&status);  
            free(tab);  

    }
}

/** QUESTION 1
 * Sur un tableau à grande dimension (10000000) on se rend compte de la différence de temps pour faire le parcours du tableau.
 * Le temps écoulé est de 0.182450 secondes. question 1
 * Le temps écoulé est de 0.157766 secondes. question 2
*/

/** QUESTION 2
 * l'affichage dans le premier est dans l'ordre d'apparition dans le tableau, contrairement à l'autre qui n'affiche pas forcement
 * dans le meme ordre car cela dépend de quel processus a affiché. Et les processus tournant en "meme temps" fait que l'affichage
 * n'est pas ordoné.
*/

///@brief fonction main contenant les tests pour répondre à la question 1 et 2
int main(int argc, char** argv){

    clock_t temps_depart, temps_arrivee;
    double temps_ecoule1, temps_ecoule2;

    printf("\tquestion1 :\n");fflush(stdout);
    temps_depart = clock();//test du premier programme
    question1();
    temps_arrivee = clock();
    temps_ecoule1 = (double)(temps_arrivee - temps_depart) / CLOCKS_PER_SEC;
    
    printf("\n\tquestion2 :\n");fflush(stdout);//test du deuxième programme
    temps_depart = clock();
    question2();
    temps_arrivee = clock();
    temps_ecoule2 = (double)(temps_arrivee - temps_depart) / CLOCKS_PER_SEC;

    printf("Le temps écoulé1 est de %f secondes.\n", temps_ecoule1);fflush(stdout);
    printf("Le temps écoulé2 est de %f secondes.\n", temps_ecoule2);fflush(stdout);

    return EXIT_SUCCESS;
}
