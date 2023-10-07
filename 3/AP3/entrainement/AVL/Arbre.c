#include "Arbre.h"
#include <stdlib.h>
#include <stdio.h>

//constructeur vide
arbre_t ConsVide(){
    return NULL;
}

//constructeur
arbre_t Cons(int val, arbre_t arb_gauche, arbre_t arb_droit){
    arbre_t nouvel_arbre = (arbre_t)malloc(sizeof(struct arbre_s));
    nouvel_arbre->feuille_droite=arb_droit;
    nouvel_arbre->feuille_gauche=arb_gauche;
    nouvel_arbre->racine=val;
    if(Hauteur(arb_droit)>Hauteur(arb_gauche)){//calcul de la hauteur de l'arbre
        nouvel_arbre->hauteur = 1+Hauteur(arb_droit);
    }else{
        nouvel_arbre->hauteur = 1+Hauteur(arb_gauche);
    }
    Equilibrage(nouvel_arbre);
    return nouvel_arbre;
}

/*AUTRE*/
arbre_t FG(arbre_t arb){
    return arb->feuille_gauche;
}

arbre_t FD(arbre_t arb){
    return arb->feuille_droite;
}

int Racine(arbre_t arb){
    return arb->racine;
}

int Hauteur(arbre_t arb){
    if(est_vide(arb)){
        return 0;
    }
    return arb->hauteur;
}

void liberer(arbre_t arb){
    if(!est_vide(arb)){
        liberer(arb->feuille_gauche);
        liberer(arb->feuille_droite);
        free(arb);
    }
}

void ModifFG(arbre_t arb, arbre_t new_FG){
    arb->feuille_gauche = new_FG;
}

void ModifFD(arbre_t arb, arbre_t new_FD){
    arb->feuille_droite = new_FD;
}

void ModifRacine(arbre_t arb, int val){
    arb->racine = val;
}

void ModifHauteur(arbre_t arb, int h){
    arb->hauteur = h;
}

int factEquilibre(arbre_t arb){
    return Hauteur(FG(arb))-Hauteur(FD(arb));
}

int est_vide(arbre_t arb){
    return arb == NULL;
}

void rotationGauche(arbre_t arb){
    if(!est_vide(FD(arb))){
        arbre_t fd = FD(arb);
        ModifFD(arb, copie(FG(fd)));
        ModifFG(fd, copie(arb));
        arb = fd;
    }
}

void rotationDroite(arbre_t arb){
    if(!est_vide(FG(arb))){
        arbre_t fg = FG(arb);
        ModifFG(arb, copie(FD(fg)));
        ModifFD(fg, copie(arb));
        arb = fg;
    }
}

void miseAJourHauteur(arbre_t arb){
    if(!est_vide(arb)){
        miseAJourHauteur(FG(arb));
        miseAJourHauteur(FD(arb));
        if(Hauteur(FG(arb))>Hauteur(FD(arb))){//calcul de la hauteur de l'arbre
            arb->hauteur = 1+Hauteur(FG(arb));
        }else{
            arb->hauteur = 1+Hauteur(FD(arb));
        }
    }
}

int estEquilibre(arbre_t arb){
    return factEquilibre(arb)<2 && factEquilibre(arb)>-2;
}

void Equilibrage(arbre_t arb){
    if(!estEquilibre(arb) && !est_vide(arb)){
        if(factEquilibre(arb)>1){
            if(factEquilibre(FG(arb))<0){
                arbre_t fg = copie(FG(arb));
                rotationGauche(fg);
                ModifFG(arb,fg);
            }
            rotationDroite(arb);
        }else if(factEquilibre(arb)<-1){
            if(factEquilibre(FD(arb))>0){
                arbre_t fd = copie(FD(arb));
                rotationDroite(fd);
                ModifFD(arb,fd);
            }
            rotationGauche(arb);
        }
    }
    miseAJourHauteur(arb);
}

void insert(arbre_t *arb, int val){
    if(est_vide(*arb)){//on ajoute au niveau des feuilles
        *arb = Cons(val,ConsVide(),ConsVide());
    }else if(val <= Racine(*arb)){
        arbre_t fg = copie(FG(*arb));
        insert(&fg,val);
        ModifFG(*arb,fg);
    }else{
        arbre_t fd = copie(FD(*arb));
        insert(&fd,val);
        ModifFD(*arb,fd);
    }
    Equilibrage(*arb);
}

int supprimerMax(arbre_t *arb){
    int max;
    if(est_vide(FD(*arb))){
        max  = Racine(*arb);
        arbre_t fg = copie(FG(*arb));
        ModifFG(*arb,ConsVide());
        liberer(*arb);
        *arb = fg;
    }else{
        arbre_t fd = copie(FD(*arb));
        max = supprimerMax(&fd);
        ModifFD(*arb,fd);
    }
    return max;
}

void supprimer(arbre_t *arb, int val){
    if(!est_vide(*arb)){
        if(Racine(*arb)<val){//la valeur se trouve à gauche
            arbre_t fd = copie(FD(*arb));
            supprimer(&fd,val);
            ModifFD(*arb,fd);
        }else if(Racine(*arb)>val){//la valeur se trouve à droite
            arbre_t fg = copie(FG(*arb));
            supprimer(&fg,val);
            ModifFG(*arb,fg);
        }else{//si la racine == val
            if(est_vide(FG(*arb)) && est_vide(FD(*arb))){
                liberer(*arb);
                *arb = NULL;
            }else if(est_vide(FD(*arb))){//seul le FD est vide
                arbre_t fg = copie(FG(*arb));
                ModifFG(*arb,ConsVide());
                liberer(*arb);
                *arb = fg;
            }else if(est_vide(FG(*arb))){//seul le FG est vide
                arbre_t fd = copie(FD(*arb));
                ModifFD(*arb,ConsVide());
                liberer(*arb);
                *arb = fd;
            }else{//on change de valeur
                arbre_t fg = copie(FG(*arb));
                int max = supprimerMax(&fg);
                ModifFG(*arb,fg);
                ModifRacine(*arb,max);
            }
        }
        if(*arb != NULL)
            Equilibrage(*arb);//on équilibre l'arbre
    }
}

int max(arbre_t arb){
    if(est_vide(arb)){//l'arbre vide n'a pas de max
        perror("un arbre vide n'a pas de maximum");
    }else{
        if(est_vide(FD(arb))){
            return Racine(arb);
        }else{
            return max(FD(arb));
        }
    }
}

int min(arbre_t arb){
    if(est_vide(arb)){//l'arbre vide n'a pas de min
        perror("un arbre vide n'a pas de minimum");
    }else{
        if(est_vide(FG(arb))){
            return Racine(arb);
        }else{
            return min(FG(arb));
        }
    }
}

arbre_t copie(arbre_t arb){
    if(!est_vide(arb)){
        return Cons(Racine(arb),copie(FG(arb)),copie(FD(arb)));
    }
    return ConsVide();
}

int taille(arbre_t arb){
    int size = 0;
    if(!est_vide(arb)){
        size = 1 + taille(FG(arb)) + taille(FD(arb));
    }
    return size;
}

int exists(arbre_t arb, int val){
    int trouve = 0;
    if(!est_vide(arb)){
        if(val == Racine(arb)){
            trouve = 1;
        }
        trouve |= exists(FG(arb),val) | exists(FD(arb),val);
    }
    return trouve;
}

void graphical_print(arbre_t a, int depth){
  if (!est_vide(a)) {
    // Appels récursifs sur le fils gauche, en augmentant le décalage
    graphical_print(FG(a),depth+3);
    // affichage de la racine 
    for(int i=0;i<depth;i++) {
      printf(" ");
    }
    printf("@--"); 
    printf("%d\n",Racine(a));
    // Appels récursifs sur le fils droit, en augmentant le décalage
    graphical_print(FD(a),depth+3);
  }
}

void graphical_print_link(arbre_t a, int depth, int trace[]){
  if(!est_vide(a)){//on verifie que l'arbre ne soit pas nul
    trace[depth]=0;//on va à gauche
    graphical_print_link(FG(a), depth+1, trace);
    for (int i=0; i<depth; ++i) {//on affiche les espaces
      if (i > 0 && trace[i] != trace[i-1]) {
        printf("|");
      }else{
        printf(" ");
      }
      printf("  ");
    }
    printf("+--");//on affiche la racine
    printf("%d",Racine(a));
    printf("\n");
    trace[depth]=1;//on va à droite
    graphical_print_link(FD(a), depth+1, trace);
  }
}

int main(void){
    //creation des arbres
    arbre_t a1 = Cons(32,Cons(30,ConsVide(),ConsVide()),ConsVide());
    arbre_t a2 = Cons(16,Cons(15,ConsVide(),ConsVide()),Cons(20,ConsVide(),a1));
    arbre_t a3 = Cons(8,ConsVide(),Cons(10,ConsVide(),a2));
    arbre_t a4 = Cons(8,copie(a3),ConsVide());

    arbre_t a5 = Cons(59, Cons(45, Cons(44,ConsVide(),ConsVide()), a2), Cons(72, Cons(67,ConsVide(),ConsVide()), Cons(84,ConsVide(),ConsVide())));

    arbre_t a = Cons(50,Cons(49,Cons(48,Cons(47,ConsVide(),ConsVide()),ConsVide()),ConsVide()),Cons(75,Cons(74,Cons(73,ConsVide(),ConsVide()),ConsVide()),ConsVide()));

    //tests
    printf("la valeur 2 est dans a3 : %d\n",exists(a4,2));
    printf("la valeur 4 est dans a3 : %d\n",exists(a4,4));

    //affichage des arbres
    int trace [Hauteur(a)];
    graphical_print_link(a,0,trace);

    printf("le max est : %d\n",max(a));

    graphical_print_link(a,0,trace);

    supprimer(&a,50);

    printf("\n\n");

    graphical_print_link(a,0,trace);

    printf("\n\n la hauteur est de %d\n",Hauteur(a));

    arbre_t a6 = Cons(4, ConsVide(), ConsVide());
    graphical_print(a6, 1);

    supprimer(&a6, 4);
    graphical_print(a6, 1);

    return EXIT_SUCCESS;
}