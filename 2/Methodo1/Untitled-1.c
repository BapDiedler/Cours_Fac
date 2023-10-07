#include <stdio.h>
#include <stdlib.h>
int main( int argc, char* argv){
	//déclaration des variables
	int a=8, b=1, tmp;
    int*p1=&a, *p2=&b;
    printf("p1: %p\np2: %p\n",p1,p2);
	//2change des valeurs
	tmp=*p1;
	*p1=*p2;
	*p2=tmp;
	//affichage
	printf("p1: %d\np2: %d\n",*p1,*p2);
    return EXIT_SUCCESS;
}