

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

typedef enum { false, true} bool;


/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

///@brief fonction calculant la valeur e en float
float Efloat () {
  float exp = 1., tmp = 1.;//tmp==1/n! == (((((1/1)/1)/2)/3)/4)/.../n)...)

  //l'arrêt se fait quand la valeur de tmp a dépassée la précision de l'ordinateur.
  // C'est à dire qu'il n'est plus capable de faire la différence entre le 0 et un très petit nombre
  for(int cpt = 1; tmp > 0; cpt++){
      tmp /= cpt;
      exp += tmp;
  }
  return exp;
}

/*************************************************/

///@brief fonction calculant la valeur e en double
double Edouble () {
  double exp = 1., tmp = 1.;
  for(int cpt = 1; tmp > 0; cpt++){
      tmp /= cpt;
      exp += tmp;
  }
  return exp;
}
  
/*************************************************/

///@brief fonction calculant la valeur e en long double
long double Elongdouble () {
  long double exp = 1., tmp = 1.;
  for(int cpt = 1; tmp > 0; cpt++){
      tmp /= cpt;
      exp += tmp;
  }
  return exp;
}

/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/

/**
 * Après avoir lancer le programme on ser rend compte que après n itérations la suite diverge. Cela est du à une erreur d'aproximation du codage des réels.
 * Car zn - yn ~ Ɛ*n!
*/

///@brief fonction affichant les n premiers termes de la suite yn = n yn−1 − 1 et y0 = e − 1 en float
void afficheYfloat (int n) {
  float res = Efloat() -1;
  printf("%f\n",res);
  for(int i=1; i<=n ; i++){
    res = i*res -1;
    printf("%f\n",res);
  }
}

/*************************************************/

///@brief fonction affichant les n premiers termes de la suite yn = n yn−1 − 1 et y0 = e − 1 en double
void afficheYdouble (int n) {
  double res = Edouble() -1;
  printf("%lf\n",res);
  for(int i=1; i<=n ; i++){
    res = i*res -1;
    printf("%lf\n",res);
  }
}

/*************************************************/

///@brief fonction affichant les n premiers termes de la suite yn = n yn−1 − 1 et y0 = e − 1 en long double
void afficheYlongdouble (int n) {
  long double res = Elongdouble() -1;
  printf("%Lf\n",res);
  for(int i=1; i<=n ; i++){
    res = i*res -1;
    printf("%Lf\n",res);
  }
}


/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/

///@brief fonction auxiliaire de la puissance 1
double power1_aux(double x, long n){
  if(n==0)
    return 1;
  return power1_aux(x,n-1)*x;
}
///@brief RECURSIF SIMPLE, PAR n-1
double power1 (double x, long n) {
  double res = power1_aux(x, labs(n));
  return n<0 ? 1./res : res; //si n<0 alors 1./res sinon res
}

/*************************************************/

///@brief ITERATIF, PAR n-1 boucle pour
double power2a (double x, long n) {
  double res = 1.;
  long m = labs(n);
  for(int i=0; i<m; i++)
    res*=x;
  return n>0 ? res : 1./res; //si n<0 alors 1./res sinon res
}

/*************************************************/

///@brief ITERATIF, PAR n-1 boucle while
double power2b (double x, long n) {
  double res = 1.;
  while(n>0){
    res*=x;
    n--;
  }
  return res;
}

/*************************************************/

///@brief SOUS-PROCEDURE, PAR n-1 avec res comme valeur de retour
void power3_aux(double x, long n, double* res){
  if(n!=0){
    *res*=x;
    power3_aux(x,n-1,res);
  }
}
///@brief RECURSIF TERMINAL AVEC SOUS-PROCEDURE, PAR n-1
double power3 (double x, long n) {
  double res = 1.;
  power3_aux(x,n,&res);
  return res;
}

/*************************************************/
///@brief SOUS-FONCTION, PAR n-1
double power4_aux(double x, long n, double res){
  if(n==0)
    return res;
  return power4_aux(x,n-1,res*x);
}
///@brief RECURSIF TERMINAL AVEC SOUS-FONCTION, PAR n-1
double power4 (double x, long n) {
  return power4_aux(x,n,1);
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n){
    if(n==0)
      return 1;
    if(n%2==0)
      return (power5(x,n/2)*power5(x,n/2)) ;
    else return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

///@brief RECURSIF SIMPLE, PAR n/2
double power6 (double x, long n) {
  if(n==0)
      return 1;
  double res = power6(x,n/2);//stocker l'appel récursif ainsi pas répété 2 fois
  if(n%2==0)
    return (res*res) ;
  return (res*res*x) ;  
}

/*************************************************/

///@brief RECURSIF SIMPLE, PAR n/2, VARIANTE
double power7 (double x, long n) {
  if(n==0)
      return 1;
  if(n%2==0)
    return (power7(x*x,n/2)) ;
  return (power7(x*x,n/2)*x) ;  
}

/*************************************************/

///@brief SOUS-FONCTION// remarque : les break sont ici inutiles car les returns font déjà des break
double power8_aux(double x, long n, double res){
  if(n==0)
      return res;
  if(n%2==0)
    return (power8_aux(x*x,n/2,res)) ;
  return (power8_aux(x*x,n/2,res*x)) ;
}
///@brief RECURSIF SIMPLE, PAR n/2, AVEC SOUS-FONCTION
double power8 (double x, long n) {
  return power8_aux(x,n,1);
}

/*************************************************/

///@brief SOUS-PROCEDURE
void power9_aux(double x, long n, double* res){
  if(n!=0){
    if(n%2!=0)
      *res*=x;
    power9_aux(x*x,n/2,res);
  }
}
///@brief RECURSIF SIMPLE, PAR n/2, AVEC SOUS-PROCEDURE
double power9 (double x, long n) {
  double res = 1.;
  power9_aux(x,n,&res);
  return res;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}


  // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}


/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/

//Une version recursive en m et iterative en n
int A1(int m, int n) {
  if(m==0)
    return n+1;
  int res = 1;
  for(int i=0; i<n+1; i++)
    res = A1(m-1,res);
  return res;
}

int Ackermann1 (int m) { return A1(m,0); }

/*************************************************/
//Une version iterative en m et recursive en n
int A3(int m, int n) {
    while (m >= 0) {
        if (m == 0) {
            return n + 1;
        }
        if (n == 0) {
            m -= 1;
            n = 1;
        } else {
            n = A3(m, n - 1);
            m -= 1;
        }
    }
    return -1;  // Cette ligne ne devrait jamais être atteinte.
}

int Ackermann3 (int m) {
  return A3(m,0);
}

/*************************************************/
int A2(int m, int n){
  if(m==0)
    return n+1;
  if(n==0)
    return A2(m-1,1);
  return A2(m-1,A2(m,n-1));
}
//Une version purement recursive
int Ackermann2 (int m) { return A2(m,0); }

/*************************************************/
int A4(int m, int n){
  return 0;
}

//version purement itérative
int Ackermann4 (int m) {
  int n=0;
  int pile[80000];//pile pour stocker les valeurs de m
  int pos_pile = 0;//position du sommet de la pile
  pile[pos_pile] = m;
  while(pos_pile>=0){//tant qu'il y a un élément dans la pile
    //dépile pour récupérer la dernière valeur de m
    m=pile[pos_pile];
    pos_pile--;
    if(m==0)//cas de base pour la récursivité sur m
      n++;
    else{
      //empile la valeur m-1
      pos_pile++;
      pile[pos_pile] = m-1;
      if(n==0)
        n=1;
      else{
        pos_pile++;
        pile[pos_pile] = m;
        n--;
      }
    }
  }
  return n;
}


typedef struct Bloc
{
    int nombre;
    struct Bloc *suivant;
} Bloc;

typedef Bloc *Liste ;

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

Liste suite(Liste l)
{
    return l->suivant ;
}

void empile(int x, Liste *L)
{
      *L = ajoute(x,*L) ; 
}

int depile(Liste *L)
{ 
  int val = (*L)->nombre;
    Liste tmp = *L ;
    *L = suite(*L) ;
    free(tmp) ;
  return val;
}

void VideListe(Liste *L)
{
    if(NOT(estVide(*L)))
    {
        depile(L);
        VideListe(L);
    }
}
/*************************************************/
/**
 * La fonction ne marche pas. Sans l'implémentation de la mémoïsation des valeurs, il n'y a aucun problème.
*/
int Ackermann5 (int m) {
  int n=0;
  Liste pile;//pile pour stocker les valeurs de m
  initVide(&pile);
  empile(m,&pile);

  while(!estVide(pile)){//tant qu'il y a un élément dans la pile
    //dépile pour récupérer la dernière valeur de m
    m=depile(&pile);
    if(m==0)//cas de base pour la récursivité sur m
      n++;
    else if(m==1)
      n += 2;
    else{
      //empile la valeur m-1
      empile(m-1,&pile);
        if(n==0)
          n=1;
        else{
          empile(m,&pile);
          n--;
        }
    }
  }
  VideListe(&pile);
  return n;
}

/*************************************************/
  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}

int ln2_aux(int n, int acc){
  if(n==1)
    return acc;
  return ln2_aux(n/2,acc+1);
}
int ln2(int n){
  if(n==0)
    return 1;
  return ln2_aux(n,1);
}

//version itérative
int X1(int n){
  int res=2;
  for(int i=0; i<n; i++){
    res+=ln2(res);
  }
  return res;
}

//version récusive
int X2(int n){
  if(n==0)
    return 2;
  int v = X2(n-1);
  return ln2(v)+v;
}


int X3_aux(int n, int acc){
  if(n==0)
    return acc;
  return X3_aux(n-1,acc+ln2(acc));
}
//version récusive terminale sous fonction
int X3(int n){
  return X3_aux(n,2);
}

int X4_aux(int n, int* acc){
  if(n!=0){
    *acc+=ln2(*acc);
    X4_aux(n-1,acc);
  }
}
//version récusive terminale sous fonction
int X4(int n){
  int acc = 2;
  X4_aux(n,&acc);
  return acc;
}


/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
  
       long nx ;
       
       int i,j,cptx ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (false) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (false) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (false) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (false) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e3 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        
}

if (false) {  
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (false) {

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        
        printf("\n") ;
      
}

if(false){
        // test pour vérifier les puissances négatives des fonctions puissances 1 et 2
        printf("Power %d dit que power(2,10) vaut %.3lf \n", i, power(2,-3,1) ) ;
        printf("Power %d dit que power(2,10) vaut %.3lf \n", i, power(2,-3,2) ) ;
        printf("\n") ;
}

        
if (false) {  

        i=9 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;

        /**
         * on remarque que quand j vaut 15 peut importe la fonction power, les erreurs de calcul sur les doubles empêche totalement la valeur correcte
        */
       
}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        /**
         * avec les lfoats, l'erreur de précision arrive dès la puissance 5
        */
        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        /**
         * avec les doubles, l'erreur de précision arrive dès la puissance 15
        */
        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        /**
         * sur les longs doubles, on se rend compte que l'on peut pousser la puissance plus long que'avec
        */
        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/
                
if (true) { 
 
        for(i=1 ; i<=5 ; i++)  // numéro de version
        for(j=0 ; j<=5 ; j++)  // test de A(j,0) pour j de 0 à 5
        
        printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;
}


/*********************************************************/


    return 0;
}