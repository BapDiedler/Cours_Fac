#include <stdio.h>
#include <stdlib.h>

//fonction qui calcule la valeur de l'exponentielle
double expo(){
    double val=1., tmp=1.;
    int cpt=0;
    for(int cpt=1; cpt<1000; cpt++){
        val+=(tmp/(double)cpt);
        tmp/=(double)cpt;
    }
    return val;
}

//fonction qui calcule la puissance d'un double à la puissance n
double Puissance(double x, int n){
    double val = 1.;
    for(int i=n; i>0; i--)
        val*=x;
    return n=0 ? 1. : val;
}

int main(void){
    printf("%f\n",Puissance(1.1,10));
    return EXIT_SUCCESS;
}