#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"
#include "jouer.h"
#include "ressource.h"


#define CHX_END 5

int main(){
	creation_plateau(6,6);
	creation_jeu();
	
	int choix = 0;
	while(choix < CHX_END){
		switch(choix){
		case 0:
			printf("Que voulez-vous faire :\n 1 - aller à droite\n 2 - aller à gauche\n 3 - aller en bas\n 4 - aller en haut\n 5 - quitter\n");
			scanf("%i",&choix);
			break;
		case CHX_END:
			break;
		default:
			dpl(choix);
			choix=0;
			affichage();
			break;
		}
	}
	return 0;
}
