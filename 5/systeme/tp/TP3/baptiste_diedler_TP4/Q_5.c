#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NB_THREADS 6 //nombre de threads

volatile int cpt_lect = 0;//compteur de lecteur dans la base de donnée
pthread_mutex_t mutex_lect = PTHREAD_MUTEX_INITIALIZER;//mutex pour bloquer les lecteurs
pthread_mutex_t mutex_ecr = PTHREAD_MUTEX_INITIALIZER;//mutex pour bloquer l'écriture
pthread_mutex_t mutex_bdd = PTHREAD_MUTEX_INITIALIZER;//mutex pour lock l'accès à la base de donnée



//FONCTION DONNEES SUR LE SUJET
//fonction de lecture
void lire(int id){

    //lock la lecture pour savoir si on lock la base de donnée ou non
    pthread_mutex_lock(&mutex_ecr);
    pthread_mutex_lock(&mutex_lect);

    if(cpt_lect==0)//on bloque l'accès à la bdd
        pthread_mutex_lock(&mutex_bdd);
    cpt_lect++;

    //on libère l'espace critique
    pthread_mutex_unlock(&mutex_lect);
    pthread_mutex_unlock(&mutex_ecr);

    printf("lire debut %d\n",id);
    usleep(rand()%500000);
    printf("lire fin %d\n",id);

    //lock la lecture pour savoir si le thread est le dernier dans la bdd
    pthread_mutex_lock(&mutex_lect);
    if(cpt_lect==1)
        pthread_mutex_unlock(&mutex_bdd);
    cpt_lect--;
    pthread_mutex_unlock(&mutex_lect);
}

//fonction d'écriture
void ecrire(int id){

    pthread_mutex_lock(&mutex_ecr);//lock car C2
    pthread_mutex_lock(&mutex_bdd);
    pthread_mutex_unlock(&mutex_ecr);

    printf("écrire debut %d\n",id);
    usleep(rand()%500000);
    printf("écrire fin %d\n",id);

    pthread_mutex_unlock(&mutex_bdd);
}

//fonction qui simule aléatoirement la lecture ou l'écriture
void* run(void* arg){
    int* id = (int*)arg;//identifiant pour repérer la famine
    while(1){
        if(rand()%2)
            lire(*id);
        else
            ecrire(*id);
    }
}


int main(void){

    int id[NB_THREADS];// tableau d'identifiant pour voir s'il y a des risques de famine.
    for(int i=0; i<NB_THREADS; i++){
        id[i] = i;
    }


    pthread_t tab[NB_THREADS];

    srand(time(NULL));//initialisation de la side rand

    for(int i=0; i<NB_THREADS; i++){//création des threads
        if(pthread_create(&tab[i], NULL, run, (void*)&id[i])){
            perror("une erreur est survenue dans la création d'un thread.\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i<NB_THREADS; i++){//attente des threads.
        if(pthread_join(tab[i], NULL)){
            perror("une erreur est survenue dans l'attente d'un thread.\n");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

/**
 * Question 1:
 * On se rend compte que avec simplement deux threads, la condition C3 n'est pas respecté.(lire début \n écrire début)
 * Par contre, la conditon C1 est respectée car (lire début \n lire début) se trouve à la suite.
 * C'est que au moins deux threads étaient en train de lire en même temps.
 * Et la C2 n'est pas non plus respecté car (écrire début \n écrire début) se qui montre bien que deux écrivains peuvent accéder à la base en même temps.
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


//QUESTION 3 VERSION 1 QUI NE PALIE PAS AU PROBLEME DE LA FAMINE NE PAS TENIR EN COMPTE

//fonction de lecture
void lire(int id){

    //lock la lecture pour savoir si on lock l'écriture ou non
    pthread_mutex_lock(&mutex_lect);

    if(cpt_lect==0)//on bloque l'accès à la bdd pour l'écriture
        pthread_mutex_lock(&mutex_ecr);
    cpt_lect++;

    //on libère l'espace critique
    pthread_mutex_unlock(&mutex_lect);

    printf("lire debut %d\n",id);
    usleep(rand()%500000);
    printf("lire fin\n");

    //lock la lecture pour savoir si le thread est le dernier dans la bdd
    pthread_mutex_lock(&mutex_lect);
    if(cpt_lect==1)
        pthread_mutex_unlock(&mutex_ecr);
    cpt_lect--;
    pthread_mutex_unlock(&mutex_lect);
}

//fonction d'écriture
void ecrire(int id){

    pthread_mutex_lock(&mutex_ecr);//lock car C2

    printf("ecrire debut %d\n",id);
    usleep(rand()%500000);
    printf("ecrire fin\n");

    pthread_mutex_unlock(&mutex_ecr);
}

//LA VERSION DANS LE CODE ACTUEL A L'AIRE DE RESOUDRE LE PROBLEME. MAIS JE N'EN N'AI AUCUNE CERTIFICATION (car seule vérification à l'aide des identifiants.)

 * Question 4: Normalement, l'algorithme donné dans le code fonctionne sans famine.
 * On se rend compte dans la première version ci-dessus que l'algorithme possède bien le problème de famine.
 * Pour palier à cela, j'ai appliquer un mutex en commun (mutex_bdd) entre la lecture et l'ecriture pour pourvoir 
 * donner un autre de priorité aux threads. Se qui n'est pas le cas dans la première version. Mais il n'y a aucune certification sue le fait qu'un thread n'attendra pas plus longtemps que les autres. Cela dépend de l'OS.
 * 
*/