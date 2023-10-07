//exo5
#include <stdlib.h>
#include <stdio.h> 
int main(int argc, char*argv[]){
    /* a;
    printf("a:\n");
    scanf("%d",&a);
    foat res;
    res=0.0;
    while (res*res!=a){
        res+=0,1;
    }
    printf("la racine de %d est: %d",a,res);*/
//fonction max entre un nombre d'entier n
    int n;
    int choix;
    choix=4;
    int max;
    max=0;
    while (choix!=0){
        if (choix==1){
            printf("entrez un numéro pour voir le quel est le plus grand: ");
            scanf("%d",&n);
            if (n>max){
                max=n;
            }
            printf("pour le moment votre valeur max est: %d",max);
        printf("choix:\n1 pour entrer une nouvelle variable\n0 pour quitter le programme\n entrez votre choix");
        scanf("%d",choix);
        }
    }
    return EXIT_SUCCESS;
}