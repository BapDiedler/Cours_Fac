
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

bool estVide(Liste l)
{
    return l == NULL ;
}

int premier(Liste l)
{
    return l->nombre ; 
}

Liste ajoute(int x, Liste l)
{
    Liste tmp = (Liste) malloc(sizeof(Bloc)) ;
    tmp->nombre = x ;
    tmp->suivant = l ;
    return tmp ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

Liste suite(Liste l)
{
    return l->suivant ;
}


void depile(Liste *L)
{
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
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

Liste copie(Liste l){
    if(estVide(l))
        return NULL;
    return ajoute(premier(l),copie(suite(l)));
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

Liste* PointeurSuite(Liste* l){
    return &(*l)->suivant;
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



//Un plus deux égal trois
int UPDET(Liste l){
    if(estVide(l))
        return 1;
    if(estVide(suite(l)))
        return premier(l)==0;
    if(estVide(suite(suite(l))))
        return premier(l)+premier(suite(l))==0;
    return premier(l)+premier(suite(l)) == premier(suite(suite(l)));
}

//Sigma liste
int S1(Liste l){
    if(estVide(l))
        return 0;
    return premier(l)+S1(suite(l));
}
int S2(Liste l){
    Liste p = l;
    int sum=0;
    while (!estVide(p)){
        sum+=premier(p);
        p = suite(p);
    }
    return sum;
}
void S3_aux(Liste l, int* sum){
    if(!estVide(l)){
        *sum+=premier(l);
        S3_aux(suite(l),sum);
    }
}
int S3(Liste l){
    int sum=0;
    S3_aux(l,&sum);
    return sum;
}
int S4_aux(Liste l, int sum){
    if(estVide(l))
        return sum;
    return S4_aux(suite(l),sum+premier(l));
}
int S4(Liste l){
    return S4_aux(l,0);
}

//Max occurences successives min
int MOSM(Liste l){
    if(estVide(l))
        return 0;
    int min=premier(l);
    int res=1;
    int min_res=1;
    Liste p=suite(l);
    while(!estVide(p)){
        if(premier(p) == min)
            res++;
        else{
            if(min > premier(p)){
                min=premier(p);
                res=1;
            }else{
                if(res > min_res)
                    min_res=res;
                res=0;
            }
        }
    }
    return res > min_res ? res : min_res;
}

//Zero en position k
int ZEPK(Liste l, int k){
    if(estVide(l) || k < 1)
        return 0;
    if(k == 1)
        return premier(l) == 0;
    return(suite(l),k-1);
}

//Zero en retro position k
int ZERPK(Liste l, int* k){
    if(estVide(l))
        return 0;
    int val=ZERPK(suite(l),k);
    if(*k--==1)
        return premier(l) == 0;
    *k--;
    return val;
}

//Difference
Liste Difference(Liste l1, Liste l2){
    if(estVide(l1))
        return copie(l2);
    if(estVide(l2))
        return copie(l1);
    if(premier(l1) < premier(l2))
        return ajoute(premier(l1),Difference(suite(l1),l2));
    if(premier(l1) > premier(l2))
        return ajoute(premier(l2),Difference(suite(l2),l1));
    return Difference(suite(l1),suite(l2));
}

void Tic_aux(Liste* l, int b){
    if(!estVide(*l)){
        if(b && premier(*l) != 0){
            empile(0,l);
            Tic_aux(PointeurSuite(PointeurSuite(l)),1);
        }else if(premier(*l) == 0){
            depile(l);
            Tic_aux(l,0);
        }
        Tic_aux(PointeurSuite(l),0);
    }
}
//Tic
void Tic(Liste* l){
    Tic_aux(l,1);
}

void AATLL(int val, Liste* l){
    if(!estVide(*l)){
        int v=premier(*l)+val;
        depile(l);
        AATLL(val,l);
        empile(v,l);
        empile(v-val,l);
    }
}
//Liste des sommes parties
Liste LDSP(Liste l){
    Liste p;
    initVide(&p);
    empile(0,&p);
    while(!estVide(l)){
        AATLL(premier(l),&p);
        l=suite(l);
    }
    return p;
}

void AATLL1(int val, Liste* l){
    if(!estVide(*l)){
        empile(premier(*l)+val,l);
        AATLL1(val,PointeurSuite(PointeurSuite(l)));
    }
}
Liste LDSP1(Liste l){
    if(estVide(l)){
        Liste l2;
        initVide(&l2);
        empile(0,&l2);
        return l2;
    }
    Liste l2 = LDSP1(suite(l));
    AATLL1(premier(l),&l2);
    return l2;
}
void aux(int p, Liste *res){
    if(!estVide(*res)){
        aux(p,PointeurSuite(res));
        empile(p+premier(*res),res);
    }
}

Liste LDSP2(Liste l){
    Liste res;
    initVide(&res);
    empile(0,&res);
    while(!estVide(l)){
        aux(premier(l),&res);
        l = suite(l);
    }
    return res;
}

//EXO 2
void truc(int* r1, int* r2, int** s3, int** s4){
    *r1=11;
    r2=malloc(sizeof(int)); *r2=12;
    **s3=13;
    *s4=malloc(sizeof(int)); **s4=14;
}
void foo(){
    int* p1=malloc(sizeof(int)); *p1=1;
    int* q1=p1;
    int* p2=malloc(sizeof(int)); *p2=2;
    int* q2=p2;
    int* p3=malloc(sizeof(int)); *p3=1;
    int* q3=p3;
    int* p4=malloc(sizeof(int)); *p4=4;
    int* q4=p4;

    truc(p1,p2,&p3,&p4);

    printf("%d, %d, %d, %d, %d, %d, %d, %d\n",*p1,*q1,*p2,*q2,*p3,*q3,*p4,*q4);
}

//EXO 3
/**
 * PE1 = O(r)
 * PE2 = O(r)
 * PE3 = O(log2(r))
 * PE4 = O(r*log2(r))
*/

//EXO 4
//Fonction catalan. LA fonction n'est pas optimale car on va recalculer les mêmes valeurs plusieurs fois. POur éviter cela on fait de la mémoïsation.
//Nous allons stocker les valeurs intermédiaires dans une tableau de taille n+1
void catalan_aux(int* tab, int n){
    int res=0;
    for(int i=0; i<n; i++){
        if(tab[i] == 0)
            catalan_aux(tab,i);
        if(tab[n-1-i] == 0)
            catalan_aux(tab,n-1-i);
        res+=(tab[i]*tab[n-1-i]);
    }
    tab[n]=res;
}
int Catalan(int n){
    int* tab=calloc(n+1,sizeof(int));
    tab[0]=1;
    catalan_aux(tab,n);
    printf("valeur de catalan : %d\n",tab[n]);
    return tab[n];
}

//EXO5
int OperateurK(int p, int i, int q){
    if(i==0)
        return p+q;
    if(q==1)
        return p;

    return OperateurK(p,i-1,OperateurK(p,i,q-1));
}

int OperateurK2(int p, int i, int q){
    if(q==1)
        return p;
    int res = 0;
    for(int j=0; j<i; j++){
        res += OperateurK(p,j,OperateurK(p,i,q-1));
    }
}

int main(void){
    foo();
    Catalan(3);
    printf("operateurk : %d\n",OperateurK(4,2,2));
    printf("\noperateurk2 : %d\n",OperateurK2(4,2,2));

    Liste l;
    initVide(&l);
    empile(10,&l);
    empile(6,&l);
    empile(5,&l);
    empile(1,&l);
    affiche_iter(LDSP2(l));
    VideListe(&l);
    return EXIT_SUCCESS;
}