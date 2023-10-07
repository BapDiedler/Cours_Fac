#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>



/*CODE PRINCIPAL DU FICHIER STATSFICHIER.C*/
int main(int argc, char** argv){


    if(argc == 2){// il doit y avoir un seul argument le nom du fichier

        struct stat s;
        char ref[1024];

        strcpy(ref, argv[1]);// on copie le nom du fichier dans le tableau ref

        if(stat(ref, &s)==-1) {//le fichier n'existe pas
            perror("le fichier/dossier n'existe pas");fflush(stdout);
            exit(1);
        }else{//le fichier existe
            if(S_ISREG(s.st_mode)){//le fichier est un fichier regulier

                printf("%s est un fichier (%ld i-node)\n",argv[1],s.st_ino);fflush(stdout);

                printf("--> taille : %ld\n",s.st_size);fflush(stdout);
                printf("--> modifier le %s",ctime(&s.st_mtime));fflush(stdout);
                printf("--> acces le %s",ctime(&s.st_atime));fflush(stdout);

                printf("====EXTRAIT====\n");
                /*FILE *f;
                char c;
                f=fopen(argv[1],"r");
                if(f != NULL){
                    int cpt = 1;
                    while((c=fgetc(f))!=EOF && cpt++ != 100){
                        printf("%c",c);
                    }
                }*/

                
                char buf;
                size_t count;
                int fd = open(argv[1],O_RDONLY);
                int i=0;
                while(read(fd,&buf,1) && i < 100){
                    printf("%c",buf);
                    i++;
                }


                printf("\n==============\n");
                close(fd);
            } else{// le fichier est un dossier

                printf("%s est un répertoire (%ld i-node)\n",argv[1],s.st_ino);fflush(stdout);

                printf("--> taille : %ld\n",s.st_size);fflush(stdout);
                printf("--> modifier le %s",ctime(&s.st_mtime));fflush(stdout);
                printf("--> acces le %s",ctime(&s.st_atime));fflush(stdout);
            }
        }

    }else{// le nombre d'arguments n'est pas bon
        printf("il doit y avoir un argument lors de l'appel (nom fichier)\n");
    }


    return EXIT_SUCCESS;
}