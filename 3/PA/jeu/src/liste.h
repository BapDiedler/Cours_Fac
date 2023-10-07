#ifndef LISTE_H
#define LISTE_H

struct Message_s{
    SDL_Rect texte_pos;
};

typedef struct Message_s _tMessage;

typedef struct Liste_s * liste;
struct Liste_s
{
   int premier;
   _tMessage* message;
   liste suivant;
};


/* SIGNATURES DES OPERATIONS PRIMITIVES */

// constructeurs
liste l_vide () ;
liste cons (int x, _tMessage * message, liste L) ;

// accès
bool est_vide (liste L) ;
int prem (liste L) ;
_tMessage * mes(liste L);
liste reste (liste L) ;
void liberer_liste (liste L) ;

/* SIGNATURES DES OPERATIONS NON PRIMITIVES */
_tMessage  * mesIndice(liste L, int i);

void afficher_liste (liste L);

#endif