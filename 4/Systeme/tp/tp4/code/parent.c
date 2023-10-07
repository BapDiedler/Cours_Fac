#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


void tre(){
    int tube[2];
    int nbJetons;

    char chaine;/* buffer d'un seul caractère */

    /* dans le code du processus écrivain :*/
    /* Fermeture du bout pour lecture pour lui*/
    close(tube[0]) ;

    for (int i = 0; i < nbJetons; i++) {
        int aleatoire = rand() % 2; // Génère un nombre aléatoire entre 0 et 1
        if (aleatoire == 0) {
            chaine = '+'; // Si le nombre aléatoire est 0, ajoute un "+"
        } else {
            chaine = '-'; // Sinon ajoute un "-"
        }
        /* écriture (buffer est une suite d'un ou plusieurs octets ici de taille char)*/
        write(tube[1],&chaine, sizeof(char)) ;
    }

    /* fin écriture */
    close(tube[1]) ;
}


int main(int argc, char** argv){

    if(argc == 2){
        int nbJetons = atoi(argv[1]);
        pid_t res,res2;
        int status;

        char lecture[5];
        char ecriture[5];



        int tube[2] ;
        if (pipe(tube) == -1){ /*création d'un tube*/
            perror("création impossible du tube");fflush(stdout);
            exit(1);
        }

        sprintf(lecture,"%d",tube[0]);
        sprintf(ecriture,"%d",tube[1]);

        /* creation du processus numero 1*/
        switch ( res = fork() ){

            case (pid_t) -1 ://erreur dans la création
                perror("création impossible");fflush(stdout);
                exit(1);

            case (pid_t) 0 ://création du fils
                printf("le fils est %d\n",getpid());fflush(stdout);
                execl("./progEnfant","progEnfant",lecture,ecriture,NULL);
                break;

            default ://espace du père
                printf("creation du premier processus : %d\n",getpid());
                break;
        }


        /* creation du processus numero 2*/
        switch (res2 = fork()){

            case (pid_t) -1://erreur dans la création
                perror("création impossible");fflush(stdout);
                exit(1);
                
            case (pid_t) 0://création du fils
                printf("le fils est %d\n",getpid());fflush(stdout);
                execl("./progEnfant","progEnfant",lecture,ecriture,NULL);
                break;

            default://espace du père
                printf("creation du deuxieme processus : %d\n",getpid());fflush(stdout);
                break;
        }


        char chaine;/* buffer d'un seul caractère */

        /* dans le code du processus écrivain :*/
        /* Fermeture du bout pour lecture pour lui*/
        close(tube[0]) ;

        for (int i = 0; i < nbJetons; i++) {
            int aleatoire = rand() % 2; // Génère un nombre aléatoire entre 0 et 1
            if (aleatoire == 0) {
                chaine = '+'; // Si le nombre aléatoire est 0, ajoute un "+"
            } else {
                chaine = '-'; // Sinon ajoute un "-"
            }
            //printf("----- %c\n",chaine);
            sleep(0.1);
            /* écriture (buffer est une suite d'un ou plusieurs octets ici de taille char)*/
            write(tube[1],&chaine, sizeof(char)) ;
        }

        /* fin écriture */
        close(tube[1]) ;
        

        return 0;
    }else{
        perror("le nombre d'argument doit être de 2");fflush(stdout);
        return 1;
    }
}