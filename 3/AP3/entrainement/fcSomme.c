#include <stdlib.h>
#include <stdio.h>

/**
 * @brief fonction qui calcul la somme de tous les éléments d'un tableau
 * 
 * @param tab 
 * @return int 
 */
int Somme(int tab[10]){
    int res = tab[0];
    for(int i=1; i<10; i++){
        res+=tab[i];
    }
    return res;
}

/**
 * @brief fonction qui modifie les stats selon le tableau
 * 
 * @param tab 
 * @param min 
 * @param max 
 * @param moy 
 */
void stats(int tab[10], int* min, int* max, int* moy){
    *min,*max,*moy = tab[0];
    for(int i=1; i<10; i++){
        if(*min>tab[i]){
            *min = tab[i];
        }
        if(*max<tab[i]){
            *max = tab[i];
            printf("test");

        }
        *moy+=tab[i];
    }
    *moy=*moy/10;
}

int main(int argc, char * argv){
    int tab[]={1,2,3,4,5,6,7,8,9,10};
    int* m;
    int* M;
    int* moy;
    stats(tab,m,M,moy);
    printf("%d/%d/%d",*m,*M,*moy);
}