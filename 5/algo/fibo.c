#include <stdlib.h>
#include <stdio.h>
/*maintenant il faut le faire avec un tableau de trois cases 
en utilisant le modulo au lieu d'avoir un tableau avec toutes les valeurs
pour le moment il fonctionne mais il prend trop de place en mémoire*/
void fibonacci(int n, int * tab){
    for(int i=2; i<=n; i++){
        tab[i] = tab[i-1]+tab[i-2];
    }
}

int main(void){
    int n = 20;
    int* tab = calloc(n+1,sizeof(int));
    if(n>0)
        tab[1] = 1;
    fibonacci(n+1,tab);
    printf("%d\n",tab[n]);
    for(int i=0; i<n+1; i++){
        printf("-%d\n",tab[i]);
    }
    free(tab);
    return EXIT_SUCCESS;
}