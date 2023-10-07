#include "ressource.h"
#include "affichage.h"
#include <stdio.h>



int affichage(){
	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			if(i == X && j == Y)
				printf("X |");
			else
				printf("%i |", PLATEAU[i][j]);	
		}
		printf("\n");
	}
	
	return 0;
	}
	
int creation_plateau(int w, int h){
	WIDTH=w;
	HEIGHT=h;
	for(int i =0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			PLATEAU[i][j] = 3;
		}
	}
	
	return 0;
}

