#include "jouer.h"
#ifndef ressource_h
#define ressource_h
#include "ressource.h"
#endif
int creation_jeu(){
	X = WIDTH/2;
	Y = HEIGHT/2;
	return 0;
	}

void dpl_micro(int sens, int *val, int max){
	if(sens==0){
		*val=*val-1;
		if(*val < 0)
			*val = max-1;
		}
	else{
		*val = (*val+1)%max;
	}
	}

int dpl(int sens){
	switch(sens){
		case 1:
			dpl_micro(1,&Y,WIDTH);
			break;
		case 2:
			dpl_micro(0,&Y,WIDTH);
			break;
		case 3:
			dpl_micro(1,&X,HEIGHT);
			break;
		default:
			dpl_micro(0,&X,HEIGHT);
			break;
		}
	return 0;
	}
