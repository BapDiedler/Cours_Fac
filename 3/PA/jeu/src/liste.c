#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "liste.h"

/* IMPLEMENTATION DES OPERATIONS PRIMITIVES */

/* Constructeurs */

liste l_vide (){
    return NULL ;
}

liste cons (int x, _tMessage * message, liste L){
    liste M ;
    /* Réservation de la mémoire nécessaire et désignation d'une adresse */
    M = malloc (sizeof (liste)) ;
    M->message = malloc(sizeof(_tMessage));
    M->premier = x ;
    M->message = message;
    M->suivant = L ;
    return M ;
}

/* Accès */
bool est_vide (liste L){
    return L == NULL ;
}

int prem (liste L){
  if (est_vide (L)){
    printf ("Calcul de prem sur liste vide !\n") ;
    exit (0) ;
  }
  return L->premier ;
}

_tMessage * mes(liste L){
  if (est_vide (L)){
    printf ("Calcul de prem sur liste vide !\n") ;
    exit (0) ;
  }
  return L->message ;
}

liste reste (liste L){
  return L->suivant ;
}

void liberer_liste (liste L){
    if (!est_vide(L)){
      liberer_liste (reste (L)) ;
      free (L);
    }
}

_tMessage* mesIndice(liste L, int i){
    if(prem(L)==i){
      return mes(L);
    }
    else{
      return mesIndice(reste(L),i);
    }
}

void afficher_liste (liste L){
  if (!est_vide(L)){
    printf("%i: %d /", prem(L),mes(L)->texte_pos.x);
    afficher_liste(reste(L));
  }
}