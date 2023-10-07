#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid1, pid2;
    char buffer[BUFFER_SIZE];

    if (argc != 3) {
        printf("Usage: bypipe <command1> <command2>\n");
        return 1;
    }

    // Création du tube de communication
    if (pipe(pipefd) == -1) {
        perror("Erreur lors de la création du tube de communication");
        return 1;
    }

    // Création du premier processus enfant pour exécuter la première commande
    pid1 = fork();

    if (pid1 == -1) {
        perror("Erreur lors de la création du premier processus enfant");
        return 1;
    }

    if (pid1 == 0) {
        // Le premier processus enfant exécute la première commande et écrit le résultat dans le tube
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execl(strcat("/bin/",argv[1]), argv[1],argv[2], NULL);
        perror("Erreur lors de l'exécution de la première commande");
        exit(1);
    }

    // Création du deuxième processus enfant pour exécuter la deuxième commande
    pid2 = fork();

    if (pid2 == -1) {
        perror("Erreur lors de la création du deuxième processus enfant");
        return 1;
    }

    if (pid2 == 0) {
        // Le deuxième processus enfant lit l'entrée depuis le tube et exécute la deuxième commande
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execl(strcat("/bin/",argv[1]), argv[1],argv[2], NULL);
        perror("Erreur lors de l'exécution de la deuxième commande");
        exit(1);
    }

    // Fermeture des extrémités inutilisées du tube
    close(pipefd[0]);
    close(pipefd[1]);

    // Attente de la fin des deux processus enfants
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}