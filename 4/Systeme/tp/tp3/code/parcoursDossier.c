#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

void afficher_profondeur(int profondeur){
    for(int i=0; i<profondeur; i++){
        printf("  ");
    }
}


/*FONCTION QUI PARCOURS LES R2PERTOIRES ET FICHIER*/
void parcourir_repertoire(char *path, int* taille ,int profondeur) {

    struct dirent *entry;
    DIR *dir = opendir(path);
    if (!dir) {//le repertoire ne s'est pas ouvert
        fprintf(stderr, "Impossible d'ouvrir le repertoire %s\n", path);
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        //on ne peut pas faire de retoure en arrière
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {

            char fullpath[1024];
            sprintf(fullpath, "%s/%s", path, entry->d_name);

            struct stat statbuf;
            if (stat(fullpath, &statbuf) != -1) {

                afficher_profondeur(profondeur);//ajout des espaces
                if (S_ISDIR(statbuf.st_mode)) {//affichage dossier

                    printf("D %s (%ld i-nodes):\n", entry->d_name,entry->d_ino);
                    int new_taille = 0;
                    parcourir_repertoire(fullpath,&new_taille,profondeur+4);
                    *taille+=new_taille;

                } else if (S_ISREG(statbuf.st_mode)) {//affichage fichier

                    printf("F %s (%ld i-nodes) ( %ld O )\n", entry->d_name, entry->d_ino,statbuf.st_size);
                    *taille += statbuf.st_size;
                }
            }else{
                perror("le fichier/dossier n'existe pas");fflush(stdout);
            }
        }
    }
    afficher_profondeur(profondeur);//ajout des espaces
    printf("Taille ( %d O )\n",*taille);
    closedir(dir);
}


/*CODE PRINCIPAL DU FICHIER STATSFICHIER.C*/
int main(int argc, char** argv){

    if(argc == 2){

        struct stat s;
        char ref[1024];

        strcpy(ref, argv[1]);// on copie le nom du fichier dans le tableau ref

        if(stat(ref, &s)==-1 && !S_ISDIR(s.st_mode)) {//le fichier n'existe pas
            perror("le dossier n'existe pas");fflush(stdout);
            exit(1);
        }

        int taille = 0;
        parcourir_repertoire(argv[1],&taille,0);

    }else{
        printf("le nombre d'arguments doit être de 2 (le nom de répertoire)\n");fflush(stdout);
    }

    return EXIT_SUCCESS;
}