#include <stdio.h>
#include <stdlib.h>

typedef struct list_t {
    int tete;
    struct list_t* suivant;
}list_s;
typedef list_s* list;


//question1
int ZeroEnPositionUnOuDeuxOuTroisAux(list L, int cpt){
    if(cpt==0 || L==NULL)
        return 0;
    if(L->tete == 0)
        return 1;
    return ZeroEnPositionUnOuDeuxOuTroisAux(L->suivant,--cpt);
}
int ZeroEnPositionUnOuDeuxOuTrois(list L){
    return ZeroEnPositionUnOuDeuxOuTroisAux(L,3);
}


//question2
int PLusCourte(list L1, list L2){
    if(L2==NULL)
        return 0;
    if(L1==NULL)
        return 1;
    return PLusCourte(L1->suivant, L2->suivant);
}


//question3 récursive simple
int NombreDe0AvantPositionK(list L, int k){
    if(L==NULL || k<0)
        return 0;
    if(L->tete == 0)
        return 1+NombreDe0AvantPositionK(L->suivant,--k);
    return NombreDe0AvantPositionK(L->suivant,--k);
}

//question3 récusive terminale
int NombreDe0AvantPositionKTAux(list L, int k, int cpt){
    if(L==NULL || k<0)
        return cpt;
    if(L->tete == 0)
        return NombreDe0AvantPositionKTAux(L->suivant,--k,++cpt);
    return NombreDe0AvantPositionKTAux(L->suivant,--k,cpt);
}
int NombreDe0AvantPositionKT(list L, int k){
    return NombreDe0AvantPositionKTAux(L,k,0);
}

//question3 récusive terminale procéduriale
void NombreDe0AvantPositionKTPAux(list L, int k, int* cpt){
    if(!(L==NULL || k<0)){
        if(L->tete == 0){
            *cpt++;
            NombreDe0AvantPositionKTPAux(L->suivant,--k,cpt);
        }
        NombreDe0AvantPositionKTPAux(L->suivant,--k,cpt);
    }
}
int NombreDe0AvantPositionKTP(list L, int k){
    int cpt=0;
    NombreDe0AvantPositionKTAux(L,k,&cpt);
    return cpt;
}

//question3 itérative
int NombreDe0avantPositionKI(list L, int k){
    int cpt=0;
    list tmp = copieList(L);
    while(L!=NULL && k>=0){
        if(tmp->tete == 0)
            cpt++;
        tmp = tmp->suivant;
    }
    return cpt;
}


//question5 récursive simple
list FctBegaye(list L){
    if(L == NULL)
        return NULL;
    if(L->tete > 0)
        return Cons(L->tete, Cons(L->tete, FctBegaye(L->suivant)));
    return FctBegaye(L->suivant);
}

//question5 récursive terminale
list FctBegayeTAux(list L, list aux){
    if(L == NULL)
        return aux;
    if(L->tete > 0)
        return Cons(L->tete, Cons(L->tete, FctBegaye(L->suivant)));
    return FctBegaye(L->suivant);
}



int main(void){
    return EXIT_SUCCESS;
}