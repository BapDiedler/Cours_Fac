#include <stdlib.h>
#include <stdio.h>
#define pi 3.14159
int main(int argc, char*argv[]){
    int c=0;//initialisation de la valeur c
    int valid=0;//variable qui va nous dire si le rayon est saisi ou pas
    float rayon=0;//initialisation du rayon
    while(c!=4){
        //énumération des choix possibles
        printf("1 pour rentrer un rayon\n2pour calculer le périmètre d'un cercle\n3 pour calculer l'aire d'un disque\n4 pour quitter");
        scanf("%d",&c);
        //condition 1
        if(c==1){
            printf("entrer la valeur du rayon:\n");
            scanf("%f",&rayon);
            valid=1;
        }
        //condition 2
        else if(c==2){
            //dans le cas où le rayon n'est pas valide
            if(valid==0){
                printf("le rayon n'ai pas validé");
            }
            //dans le cas où le rayon est valide
            else{
                float res=2*pi*rayon;
                printf("le périmètre du cercle de rayon %d est: %f\n",rayon,res);
            }
        }
        //condition 3
        else if(c==3){
            //dans le cas où le rayon n'est pas valide
            if(valid==0){
                printf("le rayon n'ai pas validé");
            }
            //dans le cas où le rayon est valide
            else{
                float res=pi*rayon*rayon;
                printf("l'aire du disque de rayon %d est: %f\n",rayon,res);
            }
        }
    }
    return EXIT_SUCCESS;
}