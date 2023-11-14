
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

/// @brief fonction qui permet de savoir si l[0]+l[1] == l[2]
/// @param l liste que l'on observe
/// @return 0 si l[0]+l[1] != l[2] et 1 si l[0]+l[1] == l[2]
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

/// @brief fonction qui permet de savoir si une liste est triée ou non
/// @param l liste que l'on observe
/// @return _0 si la liste n'est pas triée
///         _1 si la liste est triée
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

/// @brief fonction qui permet de connaitre le nombre d'éléments qui se trouve à la même position dans deux listes.
/// @param l1 première liste
/// @param l2 deuxième liste
/// @return le nombre d'éléments à la même position.
int NombreMemePosition1(Liste l1, Liste l2){
    if(estVide(l1) || estVide(l2))
        return 0;
    if(l1->nombre == l2->nombre)
        return 1+NombreMemePosition1(l1->suivant, l2->suivant);
    return NombreMemePosition1(l1->suivant, l2->suivant);
}

/// @brief fonction qui permet de connaitre le nombre d'éléments qui se trouve à la même position dans deux listes.
/// @param l1 première liste
/// @param l2 deuxième liste
/// @return le nombre d'éléments à la même position.
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


//fonction auxiliaire pour la fonction NombreMemePosition3
int NMP_aux3(Liste l1, Liste l2, int acc){
    if(estVide(l1) || estVide(l2))
        return acc;
    if(l1->nombre == l2->nombre)
        acc++;
    return NMP_aux3(l1->suivant, l2->suivant,acc);
}
/// @brief fonction qui permet de connaitre le nombre d'éléments qui se trouve à la même position dans deux listes.
/// @param l1 première liste
/// @param l2 deuxième liste
/// @return le nombre d'éléments à la même position.
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
/// @brief fonction qui permet de connaitre le nombre d'éléments qui se trouve à la même position dans deux listes.
/// @param l1 première liste
/// @param l2 deuxième liste
/// @return le nombre d'éléments à la même position.
int NombreMemePosition4(Liste l1, Liste l2){
    int acc = 0;
    NMP_aux4(l1,l2,&acc);
    return acc;
}


//fonction auxiliaire qui retire le dernier élément
Liste FVD(Liste l){
    if(estVide(l->suivant))
        return NULL;
    return ajoute(l->nombre,FVD(l->suivant));
}
/// @brief version récusive simple
/// @param l liste que l'on transforme
/// @return la nouvelle liste sans le dernier élément
Liste FonctVireDernier1(Liste l){
    if(estVide(l))
        return NULL;
    return FVD(l);
}

/// @brief version itérative
/// @param l liste que l'on transforme
/// @return la nouvelle liste sans le dernier élément
Liste FonctVireDernier2(Liste l){
    Liste nouvelleListe;
    initVide(&nouvelleListe);
    Liste * Q = &nouvelleListe;//pointeur sur le dernier élément de la liste
    while (l != NULL){//itération sur la liste
        if(!estVide(l->suivant)){
            empile(l->nombre, Q);
            Q = &(*Q)->suivant;//pointe vers le drenier élément
        }
        l = l->suivant;
    }
    return nouvelleListe;
}


/// @brief Procédure qui ajoute un élément devant le Premier 0
/// @param l Liste où l'on ajoute l'élément
/// @param x élément ajouté
void AjouteDevantPremierZero(Liste* l, int x){
    if(estVide(*l) || (*l)->nombre == 0)
        empile(x,l);
    else
        AjouteDevantPremierZero(&((*l)->suivant),x);
}



//Procédure auxiliaire de ADDZ1
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
/// @brief procédure qui ajoute un élément devant le dernier 0. La procédure est récusive sur la liste.
/// @param l liste où l'on ajoute l'élément
/// @param x élément que l'on ajoute
void AjouteDevantDernierZero1(Liste* l, int x){
    if(estVide(*l))
        empile(x,l);
    else{
        int b = 0;
        ADDZ_aux(l,x,&b);
    }
}

/// @brief procédure qui ajoute un élément devant le dernier 0. La procédure est itérative sur la liste.
/// @param l liste où l'on ajoute l'élément
/// @param x élément que l'on ajoute
void AjouteDevantDernierZero2(Liste *L, int x) {
    Liste courant = *L;
    Liste tmp = NULL;//sauvegarde du dernier 0

    if(courant == NULL){//si la liste est vide
        empile(x,L);
        return;
    }

    while(courant->suivant != NULL){//itération sur la liste
        if(premier(courant->suivant) == 0){
            tmp = courant;
        }
        courant = courant->suivant;
    }

    if(tmp == NULL){//si l'on n'a pas trouvé de 0, c'est qu'il est en tête de liste ou qu'il n'y en a pas
        if(premier(*L) == 0)
            empile(x,L);
        else
            empile(x,&(courant->suivant));
    }else//on ajoute devant le dernier 0
        empile(x,&(tmp->suivant));
}


//procédure auxiliaire.
void ADDZ3_aux(Liste* L, Liste courant, Liste tmp, int x){
    if(courant->suivant == NULL){
        if(tmp == NULL){
            if(premier(*L) == 0)
                empile(x,L);
            else
                empile(x,&(courant->suivant));
        }else
            empile(x,&(tmp->suivant));
    }else{
        if(premier(courant->suivant) == 0){
            tmp = courant;
        }
        ADDZ3_aux(L,courant->suivant,tmp,x);
    }
}
/// @brief procédure qui ajoute un élément devant le dernier 0. La procédure est récusive terminale sur la liste.
/// @param l liste où l'on ajoute l'élément
/// @param x élément que l'on ajoute
void AjouteDevantDernierZero3(Liste *L, int x) {
    Liste courant = *L;
    Liste tmp = NULL;

    if(courant == NULL){
        empile(x,L);
        return;
    }
    ADDZ3_aux(L,courant,tmp,x);
}


/// @brief procédre qui ajoute un 0 devant tous les termes non nuls qui précèdent le premier 0 
///        (s’il n’y a pas de 0: devant tous les termes) et enlève les zéros consécutifs qui suivent
/// @param l liste que l'on transforme
void TIC(Liste* l){
    if(!estVide(*l)){
        if((*l)->nombre!=0){
            empile(0,l);
            TIC(&(*l)->suivant->suivant);//appel sur PointeurSuite de PointeurSuite
        }else{
            while(!estVide(*l) && (*l)->nombre==0)
                depile(l);
        }
    }
} 

/*****************************************************/

/// @brief Fonction qui ajoute un élément en tête de toutes les listes
/// @param x 
/// @param l 
/// @return 
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
        return ajoute_of_list(ajoute(n,NULL),NULL);
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


typedef struct BlocZ
{
    int nombre;
    struct BlocZ *next;
    struct BlocZ **pre;
} BlocZ;
typedef BlocZ *ListeZ ;

typedef ListeZ **AccesListe;

ListeZ ZAjouterAvant(int x, AccesListe* acces){
    ListeZ newList = malloc(sizeof(BlocZ));

    newList->nombre = x;

    if(*acces == NULL){//Il n'y a aucun élément dans la liste
        newList->next = newList;
        newList->pre = &newList->next;
    }else{
        AccesListe tmp = *acces;

        newList->next = **tmp;
        newList->pre = *tmp;
        **tmp = newList;
        *tmp = &newList->next;

        
    }
    *acces = &newList->pre;
    return newList;
}

void ALZ_aux(ListeZ L, ListeZ* dernier, ListeZ pos){
    printf("Bloc %p : nombre->%d | %p<-next->%p | %p<-pre->%p\n",pos,L->nombre,&L->next,L->next,&L->pre,L->pre);
    if(L->pre != dernier){
        ALZ_aux(L->next, dernier, L);
    }
}
void afficherListeZ(AccesListe acces, ListeZ L){
    if(acces == NULL){
        printf("La liste est vide\n");
        return;
    }
    printf("acces : %p\n",acces);
    ALZ_aux(L->next, *acces, L);
}
void libererListeZ(ListeZ liste){
    if (liste == NULL) {
        return;  // La liste est déjà vide
    }

    ListeZ current = liste;
    ListeZ next;

    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != liste);
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
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    depile(&l1);
    depile(&l2);
    empile(0,&l2);
    empile(10,&l2);
    empile(5,&l2);
    empile(0,&l1);
    empile(5,&l1);

    AjouteDevantDernierZero2(&l1,10);
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([5;0]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    VireDernier_rec(&l1);
    initVide(&l2);

    empile(0,&l2);    
    empile(10,&l2);
    empile(5,&l2);
    AjouteDevantDernierZero2(&l1,0);
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([5;10]) -> %s\n",equals(l1,l2)?"success":"failure");

    depile(&l2);
    depile(&l2);
    depile(&l2);

    empile(0,&l2);
    empile(3,&l2);
    empile(10,&l2);
    empile(5,&l2);
    AjouteDevantDernierZero2(&l1,3);
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([5;10;0]) -> %s\n",equals(l1,l2)?"success":"failure");

    initVide(&l1);
    initVide(&l2);

    empile(3,&l1);
    empile(3,&l2);
    empile(0,&l1);
    empile(0,&l2);
    empile(1,&l2);
    AjouteDevantDernierZero2(&l1,1);
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([0;3]) -> %s\n",equals(l1,l2)?"success":"failure");


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
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    depile(&l1);
    depile(&l2);
    empile(0,&l2);
    empile(10,&l2);
    empile(5,&l2);
    empile(0,&l1);
    empile(5,&l1);

    AjouteDevantDernierZero3(&l1,10);
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([5;0]) -> %s\n",equals(l1,l2)?"success":"failure");
    
    VireDernier_rec(&l1);
    initVide(&l2);

    empile(0,&l2);    
    empile(10,&l2);
    empile(5,&l2);
    AjouteDevantDernierZero3(&l1,0);
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([5;10]) -> %s\n",equals(l1,l2)?"success":"failure");

    depile(&l2);
    depile(&l2);
    depile(&l2);

    empile(0,&l2);
    empile(3,&l2);
    empile(10,&l2);
    empile(5,&l2);
    AjouteDevantDernierZero3(&l1,3);
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([5;10;0]) -> %s\n",equals(l1,l2)?"success":"failure");

    initVide(&l1);
    initVide(&l2);

    empile(3,&l1);
    empile(3,&l2);
    empile(0,&l1);
    empile(0,&l2);
    empile(1,&l2);
    AjouteDevantDernierZero3(&l1,1);
    affiche_rec(l1);
    printf("AjouterDevantDernierZero1([0;3]) -> %s\n",equals(l1,l2)?"success":"failure");


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

void ListeZ_test(){
    AccesListe acces = NULL;
    ListeZ L = ZAjouterAvant(1,&acces);
    L = ZAjouterAvant(2,&acces);
    L = ZAjouterAvant(3,&acces);
    afficherListeZ(acces,L);
    libererListeZ(L);
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