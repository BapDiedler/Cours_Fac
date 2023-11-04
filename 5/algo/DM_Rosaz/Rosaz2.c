
#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then

typedef enum { FALSE, TRUE} bool;

/*************************************************/
/*                                               */
/*          definition type liste                */
/*                                               */
/*************************************************/

typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;
typedef Bloc *Liste ;

typedef struct Bloc_list
{
    Liste element;
    struct Bloc_list *suivant;
} Bloc_list;

typedef Bloc_list *List_of_list ;

/*************************************************/
/*                                               */
/*                predeclarations                */
/*                                               */
/*************************************************/

/* initialise une Liste � vide */
void initVide(Liste *L);


/* renvoie 1 si la Liste en parametre est vide, 0 sinon */
bool estVide(Liste l);

/* renvoie le premier element de la Liste en parametre */
int premier(Liste l);

/* renvoie une nouvelle Liste correspondant a celle en parametre, avec l'element x ajoute en haut de la pile */
Liste ajoute(int x, Liste l);

/* modifie la Liste en parametre: x est ajoute comme premier element */
void empile(int x, Liste* L);

/* renvoie une nouvelle Liste correspondant a celle en parametre sans son premier element */
Liste suite(Liste l);

/* modifie la Liste en parametre: le premier element est retire */
void depile(Liste* l);

/* affichage simple en recursif et en iteratif */
void affiche_rec(Liste l);
void affiche_iter(Liste l);

/* longueur en recursif et en iteratif */
int longueur_rec (Liste l);
int longueur_iter (Liste l);

/*  Elimination du dernier element en recursif et en iteratif  */
/*  VD est la sousprocedure utilitaire de la version recursive */
void VD (Liste *L);
void VireDernier_rec (Liste *L);
void VireDernier_iter (Liste *L);


/*************************************************/
/*                                               */
/*                briques de base                */
/*                                               */
/*************************************************/


void initVide( Liste *L)
{
    *L = NULL ;
}

void initVide_of_list( List_of_list *L)
{
    *L = NULL ;
}

bool estVide(Liste l)
{
    return l == NULL ;
}

bool estVide_of_list(List_of_list l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste premier_of_list(List_of_list l)
{
    return l->element ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

List_of_list ajoute_of_list(Liste x, List_of_list l)
{
    List_of_list tmp = (List_of_list) malloc(sizeof(Bloc_list)) ;
    tmp->element = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

void empile_of_list(Liste x, List_of_list *L)
{
      *L = ajoute_of_list(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}

List_of_list suite_of_list(List_of_list l)
{
    return l->suivant ;
}

void depile(Liste *L)
{
    if (*L != NULL)
    {
        Liste tmp = *L;
        *L = (*L)->suivant;
        free(tmp);
    }
}

/*************************************************/
/*                                               */
/*     Affiche, avec les briques de base         */
/*                                               */
/*************************************************/

void affiche_rec(Liste l)
{
    if(estVide(l))
        printf("\n");
    else
    {
        printf("%d ", premier(l));
        affiche_rec(suite(l));
    }
}

void affiche_of_list(List_of_list l)
{
    if(estVide_of_list(l))
        printf("\n");
    else
    {
        affiche_rec(l->element);
        affiche_of_list(suite_of_list(l));
    }
}


void affiche_iter(Liste l)
{
    Liste L2 = l;
    while(!estVide(L2))
    {
        printf("%d ", premier(L2));
        L2 = suite(L2);
    }
    printf("\n");
}

/*************************************************/
/*                                               */
/*     Longueur, sans les briques de base        */
/*                                               */
/*************************************************/

int longueur_rec (Liste l)
{
    if (l == NULL)
         return 0 ;
    else return (1 + longueur_rec(l->suivant)) ;
}


int longueur_iter (Liste l)
{
    Liste P = l;
    int cpt = 0 ;
    while (P ISNOT NULL)
    {   P = P->suivant ;
        cpt++ ;
    }
    return cpt ;
}

/*************************************************/
/*                                               */
/*       VireDernier,                            */
/*               sans les briques de base,       */
/*               ni le "->"                      */
/*                                               */
/*************************************************/

void VD (Liste *L)
          // *L non NULL ie liste non vide
{
     if ( ((**L).suivant) == NULL )
            depile(L) ;   // moralement : depile(& (*L)) ;
     else VD (& ( (**L).suivant )) ;
}

void VireDernier_rec (Liste *L)
{
     if ( (*L) ISNOT NULL )
          VD(L);        // moralement : VD(& (*L)) ;
}

void VireDernier_iter (Liste *L)
{
    if ( (*L) ISNOT NULL)
    {
        while ( ((**L).suivant) ISNOT NULL )
                 L = & ( (**L).suivant ) ;
        free(*L) ;
        *L = NULL ;
     }
}


/*************************************************/
/*                                               */
/*       Libere la memoire                       */
/*                                               */
/*************************************************/

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
}

void depile_of_list(List_of_list *L)
{
    List_of_list tmp = *L ;
    *L = suite_of_list(*L) ;
    VideListe(&tmp->element) ;
    free(tmp);
}

void VideListe_of_list(List_of_list *L)
{
    if(NOT(estVide_of_list(*L)))
    {
        depile_of_list(L);
        VideListe_of_list(L);
    }
}


/*************************************************/
/*                                               */
/*       Question de cours                       */
/*                                               */
/*************************************************/

int UnPlusDeuxEgaleTrois(Liste l){
    if(estVide(l))
        return 1;
    int prem = l->nombre;
    if(estVide(l->suivant))
        return prem==0;
    int snd = l->suivant->nombre;
    if(estVide(l->suivant->suivant))
        return prem+snd==0;
    int trois = l->suivant->suivant->nombre;
    return prem+snd==trois;
}

int Croissante(Liste l){
    if(estVide(l))
        return 1;
    int res = 1;//valeur de retour
    int precedant = l->nombre;//variable contenant la valeur précédante de la liste
    Liste p = l->suivant;
    while(!estVide(p) && res){
        res = precedant<=p->nombre;//comparaison de la nouvelle valeur avec la précédante
        precedant=p->nombre;
        p = p->suivant;
    }
    return res;
}


int NombreMemePosition1(Liste l1, Liste l2){
    if(estVide(l1) || estVide(l2))
        return 0;
    if(l1->nombre == l2->nombre)
        return 1+NombreMemePosition1(l1->suivant, l2->suivant);
    return NombreMemePosition1(l1->suivant, l2->suivant);
}


int NombreMemePosition2(Liste l1, Liste l2){
    int res = 0;
    while(!(estVide(l1) || estVide(l2))){
        if(l1->nombre == l2->nombre)
            res++;
        l1 = l1->suivant;
        l2 = l2->suivant;
    }
    return res;
}


//fonction auxiliaire pour la fonction NombreMemePosition
int NMP_aux3(Liste l1, Liste l2, int acc){
    if(estVide(l1) || estVide(l2))
        return acc;
    if(l1->nombre == l2->nombre)
        acc++;
    return NMP_aux3(l1->suivant, l2->suivant,acc);
}
int NombreMemePosition3(Liste l1, Liste l2){
    return NMP_aux3(l1,l2,0);
}


//procédure auxiliaire pour la fonction NombreMemePosition
void NMP_aux4(Liste l1, Liste l2, int* acc){
    if(!estVide(l1) && !estVide(l2)){
        if(l1->nombre == l2->nombre)
            (*acc)++;
        NMP_aux4(l1->suivant, l2->suivant,acc);
    }
}
int NombreMemePosition4(Liste l1, Liste l2){
    int acc = 0;
    NMP_aux4(l1,l2,&acc);
    return acc;
}

Liste FVD(Liste l){
    if(estVide(l->suivant))
        return NULL;
    return ajoute(l->nombre,FVD(l->suivant));
}
//version récusive simple
Liste FonctVireDernier1(Liste l){
    if(estVide(l))
        return NULL;
    return FVD(l);
}

//version itérative
Liste FonctVireDernier2(Liste l){
    Liste nouvelleListe;
    initVide(&nouvelleListe);
    Liste Q = NULL;
    while (l != NULL){
        if(!estVide(l->suivant)){
            if(estVide(nouvelleListe)){
                initVide(&nouvelleListe);
                empile(l->nombre, &nouvelleListe);
                Q = nouvelleListe;
            }
            else{
                empile(l->nombre, &Q->suivant);
                Q = Q->suivant;
            }
        }
        l = l->suivant;
    }
    return nouvelleListe;
}



void AjouteDevantPremierZero(Liste* l, int x){
    if(estVide(*l) || (*l)->nombre == 0)
        empile(x,l);
    else
        AjouteDevantPremierZero(&((*l)->suivant),x);
}




void ADDZ_aux( Liste *l, int x, int *b) {
    if(estVide(*l)){
        if(!(*b))
            empile(x,l);
    }else{
        if((*l)->nombre == 0)
            *b=1;
        ADDZ_aux(&(*l)->suivant,x,b);
        if((*l)->nombre == 0 && *b){
            *b=0;
            empile(x,l);
        }
    }
}
void AjouteDevantDernierZero1(Liste* l, int x){
    if(estVide(*l))
        empile(x,l);
    else{
        int b = 0;
        ADDZ_aux(l,x,&b);
    }
}


/// @brief procédure qui ajoute un x devant le dernier 0
/// @param l 
/// @param x 
void AjouteDevantDernierZero2(Liste *l, int x){
    Liste P = *l;
    Liste M = NULL;
    
    while(!estVide(P)){
        printf("coucou\n");fflush(stdout);
        if((P)->nombre == 0){
            M = P;
        }
        P = (P->suivant);
    }
    if(!estVide(M)){
        empile(x,&M);
    }
}

void AjouteDevantDernierZero3(Liste *l, int x) {
    int b = 0;
    Liste courant = *l;
    Liste precedent = NULL;

    // Cas spécial pour le premier élément
    if (!estVide(courant) && courant->nombre == 0) {
        empile(x, l);
        b = 1;
        courant = (*l)->suivant;
    }

    while (!estVide(courant)) {
        if (courant->nombre == 0) {
            if (estVide(courant->suivant)) {
                // Cas où le dernier élément est 0, ajouter x devant
                empile(x, &courant);
                
                if (estVide(precedent)) {
                    // Si le premier élément est 0, mettre à jour le pointeur de la liste
                    *l = courant;
                } else {
                    precedent->suivant = courant;
                }
                return;
            } else {
                b = 1;  // Indiquer que le dernier 0 a été trouvé
            }
        }
        precedent = courant;
        courant = courant->suivant;
    }

    if (b == 0) {
        // Si aucun 0 n'a été trouvé, ajouter x en fin de liste
        empile(x, l);
    }
}


void TIC(Liste* l){
    if(!estVide(*l)){
        if((*l)->nombre!=0){
            empile(0,l);
            TIC(&(*l)->suivant->suivant);
        }else{
            while(!estVide(*l) && (*l)->nombre==0)
                depile(l);
        }
    }
} 

List_of_list AETTL(int x, List_of_list l){
    if(estVide_of_list(l))
        return NULL;
    return ajoute_of_list(
        ajoute(x, premier_of_list(l)),
        AETTL(x, suite_of_list(l))
    );
}

List_of_list ATP(int n, Liste l){
    if(estVide(l)){
        List_of_list aux;
        initVide_of_list(&aux);
        Liste singleton;
        initVide(&singleton);
        empile(n,&singleton);
        return ajoute_of_list(singleton,aux);
    }
    return ajoute_of_list(
        ajoute(n,l),
        AETTL(premier(l),
            ATP(n,suite(l)))
        );
}

List_of_list Concat(List_of_list l1, List_of_list l2){
    if(estVide_of_list(l1))
        return l2;
    return(ajoute_of_list(premier_of_list(l1),Concat(suite_of_list(l1),l2)));
}

List_of_list ATLTP(int n, List_of_list l){
    if(estVide_of_list(l))
        return NULL;
    return Concat(
        ATP(n,premier_of_list(l)),
        ATLTP(n,suite_of_list(l))
        );
}

List_of_list Permutations(int n){
    if(n == 0){
        List_of_list l;
        initVide_of_list(&l);
        empile_of_list(NULL,&l);
        return l;
    }
    return ATLTP(n,Permutations(n-1));
}


/*************************************************/
/*                                               */
/*           Main                                */
/*                                               */
/*************************************************/

void poup (Liste l)
{
        printf("Double Affichage \n") ;
        affiche_rec(l) ;
        affiche_iter(l) ;

        printf("Longueur en double %d %d \n\n", 
                           longueur_rec(l), 
                           longueur_iter(l) 
               ) ;
}


/*****************FONCTIONS DE TEST****************************/

int equals(Liste l1, Liste l2){
    if(estVide(l1) || estVide(l2))
        return estVide(l1) && estVide(l2);
    if(l1->nombre == l2->nombre)
        return equals(l1->suivant,l2->suivant);
    return 0;
}

///@brief test de la fonction UnPLusDeuxEgalTrois
void UPDET_test(){
    Liste l;
    initVide(&l);

    printf("UnPLusDeuxEgalTrois([]) -> %s\n",UnPlusDeuxEgaleTrois(l)?"success":"failure");

    empile(3,&l);

    printf("UnPLusDeuxEgalTrois([3]) -> %s\n",UnPlusDeuxEgaleTrois(l)?"failure":"success");

    empile(2,&l);

    printf("UnPLusDeuxEgalTrois([2;3]) -> %s\n",UnPlusDeuxEgaleTrois(l)?"failure":"success");

    empile(1,&l);

    printf("UnPLusDeuxEgalTrois([1;2;3]) -> %s\n",UnPlusDeuxEgaleTrois(l)?"success":"failure");

    Liste l2;
    initVide(&l2);
    empile(0,&l2);

    printf("UnPLusDeuxEgalTrois([0]) -> %s\n",UnPlusDeuxEgaleTrois(l)?"success":"failure");

    VideListe(&l);
    VideListe(&l2);

    printf("\n");
}

/// @brief test de la fonction Croissante
void Croissante_test(){
    Liste l;
    initVide(&l);

    printf("Croissante([]) -> %s\n",Croissante(l)?"success":"failure");

    empile(3,&l);
    empile(2,&l);
    empile(1,&l);

    printf("Croissante([1;2;3]) -> %s\n",Croissante(l)?"success":"failure");

    empile(4,&l);

    printf("Croissante([4;1;2;3]) -> %s\n",Croissante(l)?"failure":"success");

    VideListe(&l);

    printf("\n");
}

/// @brief test des fonctions NombreMemePosition
void NMP_test(){
    Liste l1, l2, l3, l4;
    initVide(&l1); initVide(&l2); initVide(&l3); initVide(&l4);

    empile(2,&l2);
    empile(1,&l2);

    empile(2,&l3);
    empile(1,&l3);
    empile(2,&l3);

    empile(5,&l4);
    empile(1,&l4);
    empile(2,&l4);
    empile(2,&l4);

    for(int i=0; i<4; i++){
        switch (i){
        case 0:
            printf("NombreMemePosition1([],[]) -> %s\n",NombreMemePosition1(l1,l1)==0?"success":"failure");
            printf("NombreMemePosition1([],[1;2]) -> %s\n",NombreMemePosition1(l1,l2)==0?"success":"failure");
            printf("NombreMemePosition1([2;1;2],[1;2]) -> %s\n",NombreMemePosition1(l3,l2)==0?"success":"failure");
            printf("NombreMemePosition1([2;1;2],[5;1;2;2]) -> %s\n",NombreMemePosition1(l3,l4)==2?"success":"failure");
            printf("\n");
            break;
        case 1:
            printf("NombreMemePosition2([],[]) -> %s\n",NombreMemePosition2(l1,l1)==0?"success":"failure");
            printf("NombreMemePosition2([],[1;2]) -> %s\n",NombreMemePosition2(l1,l2)==0?"success":"failure");
            printf("NombreMemePosition2([2;1;2],[1;2]) -> %s\n",NombreMemePosition2(l3,l2)==0?"success":"failure");
            printf("NombreMemePosition2([2;1;2],[5;1;2;2]) -> %s\n",NombreMemePosition2(l3,l4)==2?"success":"failure");
            printf("\n");
            break;
        case 2:
            printf("NombreMemePosition3([],[]) -> %s\n",NombreMemePosition3(l1,l1)==0?"success":"failure");
            printf("NombreMemePosition3([],[1;2]) -> %s\n",NombreMemePosition3(l1,l2)==0?"success":"failure");
            printf("NombreMemePosition3([2;1;2],[1;2]) -> %s\n",NombreMemePosition3(l3,l2)==0?"success":"failure");
            printf("NombreMemePosition3([2;1;2],[5;1;2;2]) -> %s\n",NombreMemePosition3(l3,l4)==2?"success":"failure");
            printf("\n");
            break;
        case 3:
            printf("NombreMemePosition4([],[]) -> %s\n",NombreMemePosition4(l1,l1)==0?"success":"failure");
            printf("NombreMemePosition4([],[1;2]) -> %s\n",NombreMemePosition4(l1,l2)==0?"success":"failure");
            printf("NombreMemePosition4([2;1;2],[1;2]) -> %s\n",NombreMemePosition4(l3,l2)==0?"success":"failure");
            printf("NombreMemePosition4([2;1;2],[5;1;2;2]) -> %s\n",NombreMemePosition4(l3,l4)==2?"success":"failure");
            break;
        }
    }

    VideListe(&l1); VideListe(&l2); VideListe(&l3); VideListe(&l4);

    printf("\n");
}

///@brief test de la fonction FonctVireDernier
void FVD_test(){
    Liste l1, l2;
    initVide(&l1); initVide(&l2);

    printf("FonctVireDernier1([]) -> %s\n",estVide(FonctVireDernier1(l1))?"success":"failure");
    printf("FonctVireDernier2([]) -> %s\n",estVide(FonctVireDernier2(l1))?"success":"failure");

    empile(5,&l1);
    empile(4,&l1);
    empile(3,&l1);
    empile(4,&l2);
    empile(3,&l2);

    printf("FonctVireDernier1([3;4;5]) -> %s\n",equals(FonctVireDernier1(l1),l2) && !equals(l1,l2)?"success":"failure");
    printf("FonctVireDernier2([3;4;5]) -> %s\n",equals(FonctVireDernier2(l1),l2) && !equals(l1,l2)?"success":"failure");

    VideListe(&l1);
    VideListe(&l2);

    printf("\n");
}

///@brief test de la fonction AjouteDevantPremierZero
void ADPZ_test(){
    Liste l1, l2;
    initVide(&l1); initVide(&l2);
    empile(10,&l2);

    AjouteDevantPremierZero(&l1,10);
    printf("AjouterDevantPremierZero([]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    depile(&l1);
    depile(&l2);
    empile(0,&l2);
    empile(10,&l2);
    empile(5,&l2);
    empile(0,&l1);
    empile(5,&l1);

    AjouteDevantPremierZero(&l1,10);
    printf("AjouterDevantPremierZero([5;0]) -> %s\n",equals(l1,l2)?"success":"failure");

    VireDernier_rec(&l1);

    AjouteDevantPremierZero(&l1,0);
    printf("AjouterDevantPremierZero([5;10]) -> %s\n",equals(l1,l2)?"success":"failure");

    empile(0,&l1);
    empile(0,&l2);
    empile(3,&l2);
    AjouteDevantPremierZero(&l1,3);
    printf("AjouterDevantPremierZero([0;5;10;0]) -> %s\n",equals(l1,l2)?"success":"failure");

    VideListe(&l1);
    VideListe(&l2);

    printf("\n");
}

///@brief test de la fonction AjouteDevantPremierZero1
void ADDZ1_test(){
    Liste l1, l2;
    initVide(&l1); initVide(&l2);

    empile(10,&l2);
    AjouteDevantDernierZero1(&l1,10);
    printf("AjouterDevantDernierZero1([]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    depile(&l1);
    depile(&l2);
    empile(0,&l2);
    empile(10,&l2);
    empile(5,&l2);
    empile(0,&l1);
    empile(5,&l1);
    AjouteDevantDernierZero1(&l1,10);
    printf("AjouterDevantDernierZero1([5;0]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    VireDernier_rec(&l1);
    initVide(&l2);

    empile(0,&l2);    
    empile(10,&l2);
    empile(5,&l2);
    AjouteDevantDernierZero1(&l1,0);
    printf("AjouterDevantDernierZero1([5;10]) -> %s\n",equals(l1,l2)?"success":"failure");

    depile(&l2);
    depile(&l2);
    depile(&l2);

    empile(0,&l2);
    empile(3,&l2);
    empile(10,&l2);
    empile(5,&l2);
    AjouteDevantDernierZero1(&l1,3);
    printf("AjouterDevantDernierZero1([5;10;0]) -> %s\n",equals(l1,l2)?"success":"failure");

    initVide(&l1);
    initVide(&l2);

    empile(3,&l1);
    empile(3,&l2);
    empile(0,&l1);
    empile(0,&l2);
    empile(1,&l2);
    AjouteDevantDernierZero1(&l1,1);
    printf("AjouterDevantDernierZero1([0;3]) -> %s\n",equals(l1,l2)?"success":"failure");


    VideListe(&l1);
    VideListe(&l2);

    printf("\n");
}

///@brief test de la fonction AjouteDevantPremierZero2
void ADDZ2_test(){
    Liste l1, l2;
    initVide(&l1); initVide(&l2);
    empile(10,&l2);

    AjouteDevantDernierZero2(&l1,10);
    printf("AjouterDevantDernierZero2([]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    depile(&l1);
    depile(&l2);
    empile(0,&l2);
    empile(10,&l2);
    empile(5,&l2);
    empile(0,&l1);
    empile(5,&l1);

    affiche_iter(l1);

    AjouteDevantDernierZero2(&l1,10);

    affiche_iter(l1);
    printf("AjouterDevantDernierZero2([5;0]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    VireDernier_rec(&l1);
    initVide(&l2);

    empile(0,&l2);
    empile(10,&l2);
    empile(5,&l2);

    affiche_iter(l1);


    AjouteDevantDernierZero2(&l1,0);
    printf("AjouterDevantDernierZero2([5;10]) -> %s\n",equals(l1,l2)?"success":"failure");

    depile(&l2);
    depile(&l2);
    depile(&l2);

    empile(0,&l2);
    empile(3,&l2);
    empile(10,&l2);
    empile(5,&l2);

    affiche_iter(l1);
    affiche_iter(l2);

    AjouteDevantDernierZero2(&l1,3);
    printf("AjouterDevantDernierZero2([5;10;0]) -> %s\n",equals(l1,l2)?"success":"failure");

    VideListe(&l1);
    VideListe(&l2);

    printf("\n");
}

///@brief test de la fonction AjouteDevantPremierZero3
void ADDZ3_test(){
    Liste l1, l2;
    initVide(&l1); initVide(&l2);
    empile(10,&l2);

    AjouteDevantDernierZero3(&l1,10);
    printf("AjouterDevantDernierZero3([]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    depile(&l1);
    depile(&l2);
    empile(0,&l2);
    empile(10,&l2);
    empile(5,&l2);
    empile(0,&l1);
    empile(5,&l1);

    AjouteDevantDernierZero3(&l1,10);
    printf("AjouterDevantDernierZero3([5;0]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    VireDernier_rec(&l1);
    initVide(&l2);
    empile(0,&l2);
    empile(10,&l2);
    empile(5,&l2);


    affiche_iter(l1);
    affiche_iter(l2);

    AjouteDevantDernierZero3(&l1,0);
    printf("AjouterDevantDernierZero3([5;10]) -> %s\n",equals(l1,l2)?"success":"failure");

    depile(&l2);
    depile(&l2);
    depile(&l2);
    empile(10,&l2);
    empile(5,&l2);
    empile(0,&l2);
    empile(3,&l2);

    AjouteDevantDernierZero3(&l1,3);
    printf("AjouterDevantDernierZero3([0;5;10;0]) -> %s\n",equals(l1,l2)?"success":"failure");

    VideListe(&l1);
    VideListe(&l2);

    printf("\n");
}

void TIC_test(){
    Liste l1;
    initVide(&l1);
    TIC(&l1);
    empile(0,&l1);
    empile(10,&l1);
    empile(5,&l1);
    empile(0,&l1);
    empile(0,&l1);
    empile(0,&l1);
    empile(3,&l1);
    empile(10,&l1);
    empile(4,&l1);
    TIC(&l1);
    affiche_rec(l1);
    VideListe(&l1);
} 

void Permutation_test(){
    List_of_list l = Permutations(3);
    affiche_of_list(l);
    VideListe_of_list(&l);
}


int main(int argc, char** argv)
{/*
    Liste l ;

        initVide (&l) ;

          poup(l) ;

             empile(4, &l) ;

          poup(l) ;

             empile(5, &l) ;
             empile(6, &l) ;
             empile(7, &l) ;
             empile(8, &l) ;
             empile(9, &l) ;

          poup(l) ;

        VireDernier_rec  (&l) ;
        VireDernier_iter (&l) ;
        depile(& l) ;

          poup(l) ;

          printf(" ------ %d\n",UnPlusDeuxEgaleTrois(l));

    VideListe(&l);
*/
    Permutation_test();
    return 0;
}