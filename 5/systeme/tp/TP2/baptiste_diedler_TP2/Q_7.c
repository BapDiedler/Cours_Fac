#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void){

    int status = 0;
    int fichier;

    //création d'un processus
    switch ( fork() ){
        case (pid_t) -1 :
            perror("création impossible");
            exit(1);
        case (pid_t) 0 :
        /* on est dans le fils */

            fichier = open("stdout.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);//ouverture du fichier

            if(fichier == -1){//ouverture de stdout.txt
                perror("une erreur est survenue dans l'ouverture de stdout.txt");
                exit(EXIT_FAILURE);
            }

            if (dup2(fichier, STDOUT_FILENO) == -1){//redirection de la sortie standard
                perror("Erreur lors de la redirection de la sortie standard");
                exit(EXIT_FAILURE);
            }

            close(fichier);

            execl("/bin/ls","ls",NULL);//appel de la méthde ls dansle répertoire courant
            perror("Erreur lors de l'exécution de la commande ls");
            exit(EXIT_FAILURE);

            break;
        default :
        /* on est dans le père*/

            wait(&status);
            if(WEXITSTATUS(status)==0){
                printf("exécution validée\n");fflush(stdout);
            }else{
                printf("exécution échouée\n");fflush(stdout);
            }
    }
    return EXIT_SUCCESS;
}