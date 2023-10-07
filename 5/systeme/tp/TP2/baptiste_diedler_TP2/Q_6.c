#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * @brief test de la valeur de pos_alors
 * 
 * @param pos_alors position de la valeur alors dans les argv
 * @param argc nombre d'arguments dans la ligne de commande
 * @return quitte le programme si la valeur n'est pas correcte
*/
void test_pos_alors(int pos_alors, int argc){
    if(pos_alors<3 || pos_alors>=argc-1){
        perror("la ligne de commande n'est pas valide 'alors'");
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief test de la valeur de pos_sinon
 * 
 * @param pos_sinon position de la valeur sinon dans les argv
 * @param pos_alors position de la valeur alors dans les argv
 * @param argc nombre d'arguments dans la ligne de commande
 * @return quitte le programme si la valeur n'est pas correcte
*/
void test_pos_sinon(int pos_sinon, int pos_alors, int argc){
    if(pos_sinon<=pos_alors+1 || pos_sinon == argc-1){
        perror("la ligne de commande n'est pas valide 'sinon'");
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char** argv){

    if(argc < 5){//le nombre d'argument n'est pas valide
        perror("le nombre d'argument n'est pas valide");
        exit(EXIT_FAILURE);
    }

    int pos_alors=0, pos_sinon=0, cpt=0;
    while(cpt!=argc-1){//reherche eds position alors et sinon
        if(strcmp(argv[pos_alors],"alors")!=0)
            pos_alors++;
        if(strcmp(argv[pos_sinon],"sinon")!=0)
            pos_sinon++;
        cpt++;
    }

    //test de la position des arguments
    test_pos_alors(pos_alors, argc);
    test_pos_sinon(pos_sinon, pos_alors, argc);
    if(strcmp(argv[1],"si")!=0){//l'argument si dans la ligne de commande
        perror("la ligne de commande n'est pas valide 'si'");
        exit(EXIT_FAILURE);
    }

    int status;

    //création d'un processus
    switch (fork()){
        case (pid_t) -1 :
            perror("création impossible");
            exit(1);
        case (pid_t) 0 :
        /* on est dans le fils */
            
            execlp(argv[2], argv[2], NULL);//apelle de la première commande (argv[2]) le test

            perror("Erreur lors de l'exécution de la première commande");
            exit(EXIT_FAILURE);

            break;
        default :
        /* on est dans le père*/ 

            wait(&status);

            if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
                
                // Exécutez la ième commande (argv[i]) donc en cas de validité de la condition
                for(int i=pos_alors+1; i<=pos_sinon; i++){
                    execlp(argv[i], argv[i], NULL);
                    perror("Erreur lors de l'exécution de la ieme commande");
                    exit(EXIT_FAILURE);
                }

            }else{
                // Exécutez la ième commande (argv[i]) donc en cas de non validité de la condition
                for(int i=pos_sinon+1; i<argc; i++){
                    execlp(argv[i], argv[i], NULL);
                    perror("Erreur lors de l'exécution de la ieme commande");
                    exit(EXIT_FAILURE);
                }
            }
    }

    return EXIT_SUCCESS;
}