#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree_primitives.h"

int main()
{

  s_base_t sl = {"Stanislas","roi Pologne"};
  tree_t asl = cons(sl,cons_empty(),cons_empty());
  
  s_base_t co = {"Catherine Opalińska","reine Pologne"};
  tree_t aco = cons(co,cons_empty(),cons_empty());

  s_base_t ml = {"Marie Leszcińska","princesse Pologne"};
  tree_t aml = cons(ml,asl,aco);

  s_base_t lf = {"Louis de France","roi France"};
  tree_t alf = cons(lf,cons_empty(),cons_empty());

  s_base_t mas = {"Marie-Adélaïde de Savoie","princesse de Savoie"};
  tree_t amas = cons(mas,cons_empty(),cons_empty());

  s_base_t lvx = {"Louis XV","roi France"};
  tree_t alvx = cons(lvx,alf,amas);

  s_base_t ldf = {"Louis de France","dauphin France"};
  tree_t aldf = cons(ldf,aml,alvx);

  s_base_t mjs = {"Marie-Josèphe de Saxe","dauphine"};
  tree_t amjs = cons(mjs,cons_empty(),cons_empty());

  s_base_t lxvidf = {"Louis XVI de France","roi France"};
  tree_t alxvidf = cons(lxvidf,aldf,amjs);

  s_base_t jc = {"Jules César","empereur Rome"};

  /* Test de l'affichage sous forme d'arbre */
  graphical_print(aldf,1);
  printf("\n"); 

  int h = height(aldf);
  int trace[h];
  graphical_print_link(aldf,0,trace);

  /* Test des fonctions de récupération de la valeur et de la taille */
  printf("\n"); 
  print(ldf);
  printf(" a %d ancetres \n", size(aldf)-1);


  /* Test de la fonction de calcul de la hauteur de l'arbre */
  printf("\nOn connait des ancetres de "); 
  print(ldf);
  printf("\n     à maximum %d generations \n",  height(aldf)-1);

  /* Test de la fonction d'appartenance d'un noeud dans un arbre */
  printf("\n");
  print(sl);
  if (exists(aldf,sl)) {
    printf(" est un ancetre de ");
  } else {
    printf(" n'est pas un ancetre de ");
  }
  print(ldf);
  printf("\n");

  printf("\n");
  print(jc);
  if (exists(aldf,jc)) {
    printf(" est un ancetre de ");
  } else {
    printf(" n'est pas un ancetre de ");
  }
  print(ldf);
  printf("\n");

  printf("\n");

  /* Test de libération de la mémoire allouée pour les arbres 
   * N'hésitez pas à utiliser valgrind pour trouver vos fuites mémoire
   */
  free_tree(alxvidf);

}

