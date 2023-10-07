#include<stdio.h>
#include<stdlib.h>
#include "tree_primitives.h"

tree_t cons_empty()
{
  return NULL; 
}

tree_t cons(s_base_t v, tree_t fg, tree_t fd)
{
  tree_t new_tree = malloc(sizeof(s_node_t));//allocation de la mémoire pour le nouvel arbre
  new_tree->fd = fd;
  new_tree->fg = fg;
  new_tree->val = v;
  return new_tree; 
}

int is_empty(tree_t a)
{
  return a == NULL;//si l'arbre est vide alors il est null
}

s_base_t value(tree_t a)
{
  s_base_t dummy =  {"",""};
  if(!is_empty(a)){//l'arbre ne doit pas être vide
    dummy = a->val;
  }
  return dummy;
}

tree_t left(tree_t a)
{
  return a->fg;
}

tree_t right(tree_t a)
{
  return a->fd; 
}

void change_value(tree_t pa, s_base_t new_value)
{
  pa->val = new_value;
}

void change_left(tree_t pa, tree_t new_left)
{
  pa->fg = new_left;
}

void change_right(tree_t pa, tree_t new_right)
{
  pa->fg = new_right;
}

void free_tree(tree_t a)
{
  if(!is_empty(a)){//on regarde que l'arbre ne soit pas vide
    free_tree(left(a));
    free_tree(right(a));
    free(a);
  }
}

void prefix(tree_t a)
{
  if(!is_empty(a)){//si l'arbre n'est pas vide
    prefix(left(a));
    print(a->val);
    prefix(right(a));
  }
}

void graphical_print(tree_t a, int depth)
{
  if(!is_empty(a)){//si l'arbre n'est pas vide
    for(int i=0; i<=depth; i++){
      printf(" ");
    }
    printf("+--");
    print(a->val);
    printf("\n");
    graphical_print(left(a),depth+3);
    graphical_print(right(a),depth+3);
  }
}


void graphical_print_link(tree_t a, int depth, int trace[]) {
  if(!is_empty(a)){//on verifie que l'arbre ne soit pas nul
    trace[depth]=0;//on va à gauche
    graphical_print_link(left(a), depth+1, trace);
    for (int i=0; i<depth; ++i) {//on affiche les espaces
      if (i > 0 && trace[i] != trace[i-1]) {
        printf("|");
      }else{
        printf(" ");
      }
      printf("  ");
    }
    printf("+--");//on affiche la racine
    print(value(a));
    printf("\n");
    trace[depth]=1;//on va à droite
    graphical_print_link(right(a), depth+1, trace);
  }
}

int size(tree_t a)
{
  int s = 0;
  if(!is_empty(a)){
    s++;
    if(!is_empty(right(a))){//calcul de la taille du fils droit
      s += size(right(a));
    }
    if(!is_empty(left(a))){//calcul de la taillz du fils gauche
      s += size(left(a));
    }
  }
  return s;
}

int height(tree_t a)
{
  if(!is_empty(a)){
    if(height(left(a))>height(right(a))){//si le fils gauche est plus grand que le fils droit
      return 1 + height(left(a));
    }else{//si le fils gauche est plus petit que le fils droit
      return 1 + height(right(a));
    }
  }
  return 0;
}

int exists(tree_t a, s_base_t v)
{
  int efg = 0;
  int efd = 0;
  int er = 0;
  if(!is_empty(a)){
    if(!compare(v,value(a))){//on regarde si la racine est égale à v
      er = 1;
    }
    efg = exists(right(a),v);
    efd = exists(left(a),v);
  }
  return er || efd || efg;
}




