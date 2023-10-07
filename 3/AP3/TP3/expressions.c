#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree_primitives.h"

int main(void)
{
  tree_t arb = cons(3,1,cons(0,2,cons_empty(),cons_empty()),cons(0,3,cons_empty(),cons_empty()));
  int h = height(arb);
  int trace[h];
  graphical_print_link(arb,0,trace);
  rotation_left(arb);
  graphical_print_link(arb,0,trace);

  free_tree(arb);
  return EXIT_SUCCESS;
}






