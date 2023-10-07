#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "tree_primitives.h"

#define PI 3.14159265

tree_t cons_empty()
{
  /* Pas besoin d'allouer de la mémoire inutilement et de créer un nœud.
   * Retourner NULL suffit. */
  return NULL; 
}

tree_t cons(s_base_t v, tree_t fg, tree_t fd)
{
  /* On alloue uniquement la mémoire pour le nœud que l'on crée. v, fg et fd
   * ont déjà été créés, la mémoire a donc déjà été allouée.*/
  tree_t a = (tree_t) malloc(sizeof(s_node_t));
  /* affectations */
  a->val = v ;
  a->fg = fg;
  a->fd = fd ;
  return a ; 
}

int is_empty(tree_t a)
{
  /* Dans le cas où la restitution de l'arbre vide serait implémentée
   * différemment, le test de vacuité serait différent : il faudrait tester les
   * pointeurs de a */
  return a == NULL;
}

s_base_t value(tree_t a)
{
  return a->val;
}

tree_t left(tree_t a)
{
  return a->fg ; 
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
  pa->fd = new_right; 
}

void free_tree(tree_t a)
{
  /* test indispensable pour traiter le cas de l'arbre vide à libérer */
  if(!is_empty(a)) {
  /* On libére d'abord récursivement la mémoire sur les fils gauche et
   * droit, puis sur le nœud lui-même. */
    free_tree(left(a));
    free_tree(right(a));
    free(a);
  }
}

/* Parcours préfixe : donnée préfixe(fils_gauche) préfixe(fils_droit) */
void prefix(tree_t a)
{
  /* Test pour traiter le cas de l'arbre vide */
  if (!is_empty(a)) {
    /* Affichage de la donnée de l'arbre */
    print(value(a));
    // Appels récursifs sur les fils gauche et droit
    prefix(left(a));
    prefix(right(a));
  }
}

/* On passe la profondeur en paramètre pour obtenir une indentation cohérente */
void graphical_print(tree_t a, int depth)
{
  if (!is_empty(a)) {
    // Appels récursifs sur le fils gauche, en augmentant le décalage
    graphical_print(left(a),depth+3);
    // affichage de la racine 
    for(int i=0;i<depth;i++) {
      printf(" ");
    }
    printf("@--"); 
    print(value(a));
    printf("\n");
    // Appels récursifs sur le fils droit, en augmentant le décalage
    graphical_print(right(a),depth+3);
  }
}


int size(tree_t a)
{
  int size_a=0;
  if (!is_empty(a)) {
    /* La taille d'un arbre correspond à la somme des tailles de ses fils + 1
     * (le nœud courrant. If faut donc faire deux appels récursifs. */
    size_a = 1 + size(left(a)) + size(right(a)); 
  }
  //Dans le cas de l'arbre vide, la taille vaut 0 (initialisation de size_a en
  //début de fonction)
  return size_a;
}

int height(tree_t a)
{
  int height_a=0;
  if (!is_empty(a)) {
    /* La hauteur d'un arbre correspond à 1 + le max des hauteurs de ses fils.
     * Il faut donc deux appels récursifs.
     * Comme il faut accéder deux fois à la hauteur d'un fils, on stocke les
     * hauteurs dans des variables pour plus d'efficacité.
     */
    int hfg=height(left(a));
    int hfd=height(right(a));
    height_a = 1+((hfg) > (hfd) ? hfg : hfd);
  }
  return height_a;
}

/* On peut aussi implémenter cette fonction en utilisant un _Bool. Mais on
 * tâche d'être cohérent si on a commencé à implémenter compare() sans _Bool
 * mais avec des int. */
int exists(tree_t a, s_base_t v)
{
  if (is_empty(a)) {
    return 0;
  } else {
    if (compare(value(a),v)==0) {
      return 1;
    } else {
      /* Appels récursifs : si on n'a pas trouvé v, il faut tester sa présence
       * dans les fils gauche et droit */
      return (exists(left(a),v) || exists(right(a),v));
    }
  }
}




/****************************************************
 * Partie specifique aux expressions mathematiques
 *****************************************************/

void tree_print(tree_t a)
{
  if(!is_empty(a)){
    if(height(a)>1){
      if(value(a).nature==Fonction){
        print(value(a));
        printf("(");
        tree_print(left(a));
        printf(")");
      }else{
        printf("(");
        tree_print(left(a));
        print(value(a));
        tree_print(right(a));
        printf(")");
      }
    }else if(height(a)==1){
      print(value(a));
    }
  }
}

double evaluate(tree_t a, int val){
  double res=0;
  if(!is_empty(a)){
    s_base_t racine = value(a);
    switch (racine.nature){
      case Variable://si la racine est une variable
        res = val;
        break;
      case Binaire://si la racine est un binaire
        switch (*racine.oper){
          case '+'://addition
            res = evaluate(left(a),val) + evaluate(right(a),val);
            break;
          case '-'://soustraction
            res = evaluate(left(a),val) - evaluate(right(a),val);
            break;
          case '*'://multiplication
            res = evaluate(left(a),val) * evaluate(right(a),val);
            break;
          case '/'://division
            res = evaluate(left(a),val) / evaluate(right(a),val);
            break;
          default:
            break;
        }
        break;
      case Fonction://si la racine est une fonction
        switch (racine.oper[0]){
          case 's':
            res = sin(evaluate(left(a),val));
            break;
          case 'c':
            res = cos(evaluate(left(a),val));
            break;
          case 'e':
            res = exp(evaluate(left(a),val));
            break;
          case 'l':
            res = log(evaluate(left(a),val));
            break;
          case 't':
            res = tan(evaluate(left(a),val));
            break;
        }

      default:
        res = racine.val;
        break;
    }
  }
  return res;
}

/// @brief fonction qui fait une copie de l'arbre
/// @param a 
/// @return tree_t
tree_t copy_tree(tree_t a){
  if(!is_empty(a)){
    tree_t new_a = new_a = cons(value(a),copy_tree(left(a)),copy_tree(right(a)));;
    return new_a;
  }
  return cons_empty();
}

tree_t derivate(tree_t a){
  s_base_t cnst={Constante,0,""};
  s_base_t valN={Constante,-1,""};
  tree_t res=cons(cnst,cons_empty(),cons_empty());

  s_base_t racine = value(a);//on récupère la racine de l'abre
  switch (racine.nature){
    case Variable://si la racine est une variable
      cnst.val = 1;
      change_value(res,cnst);
      break;
    case Binaire://si la racine est un opérateur binaire
      switch (*racine.oper){
        case '+'://si on derive on a un addition
          //res = cons(racine,derivate(left(a)),derivate(right(a)));
          change_value(res,racine);
          change_left(res,derivate(left(a)));
          change_right(res,derivate(right(a)));
          break;
        case '-'://si on derive on a un soustraction
          change_value(res,racine);
          change_left(res,derivate(left(a)));
          change_right(res,derivate(right(a)));
          break;
        case '*'://en cas de multiplication
          cnst.oper = "+";
          cnst.nature = Binaire;
          change_value(res,cnst);
          change_left(res,cons(racine,derivate(left(a)),copy_tree(right(a))));
          change_right(res,cons(racine,copy_tree(left(a)),derivate(right(a))));
          break;
        case '/'://en cas de division
          cnst.oper = "*";
          cnst.nature = Binaire;
          tree_t denominateur = cons(cnst,copy_tree(left(a)),copy_tree(left(a)));
          tree_t numerateur_gauche = cons(cnst,derivate(right(a)),copy_tree(left(a)));
          tree_t numerateur_droit = cons(cnst,copy_tree(right(a)),derivate(left(a)));
          cnst.oper = "-";
          tree_t numerateur = cons(cnst,numerateur_gauche,numerateur_droit);
          change_value(res,racine);
          change_left(res,numerateur);
          change_right(res,denominateur);
          break;
      }
      break;
    case Fonction://si la racine est une fonction
      switch(racine.oper[0]){
        case 's':
          cnst.nature = Binaire;
          cnst.oper = "*";
          change_value(res,cnst);
          change_left(res,derivate(left(a)));
          racine.oper = "cos";
          change_right(res,cons(racine,copy_tree(left(a)),cons_empty()));
          break;
        case 'c':
          cnst.nature = Binaire;
          cnst.oper = "*";
          change_value(res,cnst);
          change_left(res,derivate(left(a)));
          racine.oper = "sin";
          tree_t fonc = cons(cnst,cons(valN,cons_empty(),cons_empty()),cons(racine,copy_tree(left(a)),cons_empty()));
          change_right(res,fonc);
          break;
        case 'l':
          cnst.nature = Binaire;
          cnst.oper = "*";
          change_value(res,cnst);
          change_right(res,copy_tree(a));
          change_left(res,derivate(left(a)));
          break;
        case 'e':
          cnst.nature = Binaire;
          cnst.oper = "*";
          change_value(res,cnst);
          change_right(res,copy_tree(a));
          change_left(res,derivate(left(a)));
          break;
      }
      break;
    default:
      break;
  }
  return res;
}

tree_t build_tree(const char* exp, int debut, int* fin){
  s_base_t cnst={Binaire,0,""};
  tree_t res=cons(cnst,cons_empty(),cons_empty());
  
  if(exp[debut]=='('){
    char* cara = malloc(sizeof(char)*2);
    tree_t op1 = build_tree(exp,debut+1,fin);
    debut = (*fin);
    cara[0] = exp[debut];
    cara[1] = '\0';
    s_base_t op = {Binaire,0,cara};
    tree_t op2 = build_tree(exp,debut+1,fin);
    debut = (*fin)+1;
    change_value(res, op);
    change_left(res, op1);
    change_right(res,op2);
  }else if(exp[debut]=='X'){
    char* cara = malloc(sizeof(char)*2);
    cnst.nature = Variable;
    cara[0] = exp[debut];
    cara[1] = '\0';
    debut++;
    s_base_t op = {Binaire,0,cara};
    res = cons(op,cons_empty(),cons_empty());
  }else if(exp[debut]>='0' && exp[debut]<='9' && exp[debut]!='\0'){
    int cpt=0;
    char cara [10];
    cnst.nature = Constante;
    do{
      cara[cpt] = exp[debut];
      debut++;
      cpt++;
    }while(exp[debut]>='0' && exp[debut]<='9' && exp[debut]!='\0');
    cara[cpt] = '\0';
    cnst.val = atoi(cara);
    res = cons(cnst, cons_empty(), cons_empty());
  }else{
    char* cara = malloc(sizeof(char)*2);
    debut = (*fin)+1;
    cnst.nature = Fonction;
    int cpt = 0;
    do{
      cara[cpt] = exp[debut];
      debut++;
      cpt++;
    }while(exp[debut]>='a' && exp[debut]<='z' && exp[debut]!='\0');
    cara[cpt] = '\0';
    s_base_t op = {Fonction,0,cara};
    tree_t op1 = build_tree(exp,debut+1,fin);
    debut = *fin;
    res = cons(op,op1,cons_empty());
  }
  *fin = debut;
  return res;
}


