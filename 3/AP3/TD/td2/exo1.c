#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

liste trouveChemin(liste L, int* caseDeb[2], int* caseFin[2]){
    int** tmp[2]={0,0};
    if(caseDeb[0]==caseFin[0]){//on reste sur la meme ligne
        if(caseDeb[1]==caseFin[1]){//on reste sur la meme colonne
            return cons(caseDeb,L);
        }
        else if(caseDeb[1]<caseFin[1]){//on dessant d'une case
            tmp[0]=caseDeb[0];
            tmp[1]=caseDeb[1]+1;
            return trouveChemin(cons(caseDeb,L),tmp,caseFin);
        }
        else{
            tmp[0]=caseDeb[0];
            tmp[1]=caseDeb[1]-1;
            return trouveChemin(cons(caseDeb,L),tmp,caseFin);
        }
    
    }
}


int main(int argc, char** argv){
    return EXIT_SUCCESS;
}
