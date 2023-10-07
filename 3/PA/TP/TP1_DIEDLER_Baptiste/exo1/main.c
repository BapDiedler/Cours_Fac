#include <stdio.h>
#include <stdlib.h>
#include "addition.h"

int main(void){
    int a = 0, b = 0;
    printf("entrez un entier : ");
    scanf("%d",&a);
    printf("entrez un autre entier : ");
    scanf("%d",&b);
    printf("la somme des deux entiers est : %d\n",somme(a,b));
    return EXIT_SUCCESS;
}