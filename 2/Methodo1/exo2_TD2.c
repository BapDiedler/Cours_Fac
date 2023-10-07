#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* argv){
	//exo1
	/*
	l'adresse de lapemière case est 0
	l'adresse e la dernière case est '0d4194303' = '0x3fffff'
	*/
	/*
	adresse des variables:
	-a=0-3
	-b=4-7
	-p1=8-11 de plus p1 prend la valeur 0 (l'adresse de a)
	-a prend la valeur 5
	-p1 point vers elle même
	-c=12 car char est 1 octet cprend la valeur '0'
	-d=13 car char est 1 octet d prend le caractère 'd'
	-p2=14 et p2 vaut l'adresse de c
	-b prend la valeur de a+2 soit 7
	-a prend 0 qui est la valeur de c
	-x=18-22 et il prend la valeur 1.1
	-x prend la valeur de a en float sit 0.0
	*/
	/*
	//exo2
	//partie 1
	int a=4;
	int*p=&a;
	//partie 2
	printf("la valeur de a : %d\n",a);
	printf("l'adresse de a(1) : %p\n",p);
	printf("l'adresse de a(2) : %d\n",&a);
	printf("le pointeur a comme adresse : %d\n",&p);
	*/
	//exo3
	
	int a=8;
    int b=1;
    int*p1=&a;
	int*p2=&b;
    printf("p1: %p\np2: %p\n",p1,p2);
	int*p3;
	*p3=*p1;
	*p1=b;
	*p2=*p3;
	printf("p1: %d\np2: %d\n",*p1,*p2);
	
	//exo4
	/*
	à la fin du programme les variables sont: a=4 *p2=6
	*/
    return EXIT_SUCCESS;
}