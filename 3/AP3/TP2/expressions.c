#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree_primitives.h"

int main()
{
  s_base_t c1 = {Constante,1,""};
  s_base_t vx = {Variable,0,"X"};
  s_base_t plus = {Binaire,0,"+"};
  
  tree_t ac1 = cons(c1,cons_empty(),cons_empty());
  tree_t avx = cons(vx,cons_empty(),cons_empty());
  tree_t aplus1 = cons(plus,avx,ac1);

  printf("Expression : "); 
  tree_print(aplus1);
  printf("\n");
  int h = height(aplus1);
  graphical_print(aplus1,0);
  int val=2;
  printf("Valeur en %d : %f\n", val, evaluate(aplus1,val));

  printf("\n");
  

  int fin;
  tree_t arb = build_tree("((X+2)*(1+X))",0,&fin);
  printf("Expression : ");
  tree_print(arb);
  printf("\n");
  h = height(arb);
  graphical_print(arb,0);
  printf("Valeur en %d : %f", val, evaluate(arb,val));
  printf("\nPREFIX : ");
  prefix(arb);

  printf("\n");
  tree_t deriv=derivate(arb);
  printf("\nDERIVATIVE : ");
  tree_print(deriv);
  printf("\n");
  h = height(deriv);
  graphical_print(deriv,0);

  printf("\n");
  printf("Expression : \n");
  tree_t asin = build_tree("(1+sin(X))",0,&fin);
  graphical_print(asin,0);
  tree_print(asin);
  printf("\nValue 90: %f", evaluate(asin,90));
  printf("\nValue 180: %f", evaluate(asin,180));
  tree_t deriv_sin=derivate(asin);
  printf("\nDERIVATIVE : ");
  tree_print(deriv_sin);
  printf("\n");
  h = height(deriv_sin);
  graphical_print(deriv_sin,0);

  free_tree(aplus1);
  free_tree(arb);
  free_tree(deriv);
  free_tree(asin);
  free_tree(deriv_sin);
}






