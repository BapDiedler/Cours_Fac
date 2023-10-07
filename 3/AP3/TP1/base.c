#include<stdlib.h>
#include<stdio.h>
#include<string.h> //pour pouvoir utiliser strcmp()
#include "base.h"

#define BASE_STR_SIZE_ADD 6 /* = " - " + " -" + "\0" */
 
/* 
 * Fonction de comparaison de deux données.
 * Un simple test == ne suffit pas, il est nécessaire de comparer les deux
 * champs de la structure qui sont des chaînes (donc utilisation de strcmp()
 */
int compare(s_base_t t1, s_base_t t2)
{
  if(strcmp(t1.name,t2.name)==0){
    return strcmp(t1.title,t2.title);
  }else{
    return strcmp(t1.name,t2.name);
  }
}

/*
 * Fonction qui affiche la chaîne représentant la structure.
 */
void print(s_base_t t)
{
  printf("%s - %s -",t.name, t.title);
}
