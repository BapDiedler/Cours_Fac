#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*Structure permettant de représenter une image en noir et blanc*/
typedef struct bloc_image{
    bool toutnoir;//true si noir flase si blanc
    struct bloc_image* fils[4];//contient les possible 4 sous images
} bloc_image;
typedef bloc_image* image;

/**
 * @brief constructeur d'image blanche
 * 
 * @return nouvelle image
 */
image Construit_Blanc(){
    image I = (image)malloc(sizeof(bloc_image));
    I->toutnoir = false;
    for(int i=0; i<4; i++)
        I->fils[i] = NULL;
    return I;
}

/**
 * @brief constructeur d'image blanche
 * 
 * @return nouvelle image
 */
image Construit_Noir(){
    image I = (image)malloc(sizeof(bloc_image));
    I->toutnoir = true;
    for(int i=0; i<4; i++)
        I->fils[i] = NULL;
    return I;
}

/**
 * @brief constructeur d'image composée
 * 
 * @param image bloc en haut à gauche
 * @param image bloc en haut à droite
 * @param image bloc en bas à gauche
 * @param image bloc en bas à droite
 * @return la nouvelle image
 */
image Construit_Composee(image i0, image i1, image i2, image i3){
    image I = (image)malloc(sizeof(bloc_image));
    I->toutnoir = NULL;
    I->fils[0] = i0;
    I->fils[1] = i1;
    I->fils[2] = i2;
    I->fils[3] = i3;
    return I;
}

/**
 * @brief affichage en mode simple
 * 
 * @param iamge image à afficher
 */
void affichage_simple(image I){
    if(I != NULL){
        if(I->toutnoir == NULL){//passage en sous image
            printf("(");
            for(int i=0; i<4; i++)
                affichage_simple(I->fils[i]);
            printf(")");
        }else if(I->toutnoir)//image noire
            printf("N");
        else//image blanche
            printf("B");
    }
}

/**
 * @brief affichage en mode simple préfixe
 * 
 * @param iamge image à afficher
 */
void affichage_simple_plus(image I){
    if(I != NULL){
        if(I->toutnoir == NULL){//passage en sous image
            printf("+");
            for(int i=0; i<4; i++)
                affichage_simple_plus(I->fils[i]);
        }else if(I->toutnoir)//image noire
            printf("N");
        else//image blanche
            printf("B");
    }
}

/**
 * @brief affichage en mode profondeur auxiliaire
 * 
 * @param iamge image à afficher
 * @param int profondeur sur laquelle on travaille
 */
void affichage_prof_aux(image I, int prof){
    if(I != NULL){
        if(I->toutnoir == NULL){//passage en sous image
            printf("(");
            for(int i=0; i<4; i++)
                affichage_prof_aux(I->fils[i],prof+1);
            printf(")");
        }else if(I->toutnoir)//image noire
            printf("N%d",prof);
        else//image blanche
            printf("B%d",prof);
    }
}
/**
 * @brief affichage en mode profondeur
 * 
 * @param iamge image à afficher
 */
void affichage_profondeur(image I){
    affichage_prof_aux(I,1);
}

/**
 * @brief affichage en mode profondeur auxiliaire préfixé
 * 
 * @param iamge image à afficher
 * @param int profondeur sur laquelle on travaille
 */
void affichage_prof_plus_aux(image I, int prof){
    if(I != NULL){
        if(I->toutnoir == NULL){//passage en sous image
            printf("+");
            for(int i=0; i<4; i++)
                affichage_prof_plus_aux(I->fils[i],prof+1);
        }else if(I->toutnoir)//image noire
            printf("N%d",prof);
        else//image blanche
            printf("B%d",prof);
    }
}
/**
 * @brief affichage en mode profondeur préfixé
 * 
 * @param iamge image à afficher
 */
void affichage_profondeur_plus(image I){
    affichage_prof_plus_aux(I,1);
}

/**
 * @brief fonction qui permet de savoir si une image est blanche
 * 
 * @param image image à vérifier
 * @return vrai si l'image est blanche et faux sinon
 */
bool EstBlanche(image I){
    if(I == NULL)
        return true;
    if(I->toutnoir)
        return false;
    if(!I->toutnoir)
        return true;
    bool tmp = true;
    for(int i=0; i<4; i++)
        tmp &= EstBlanche(I->fils[i]);
    return tmp;
}

/**
 * @brief fonction qui permet de savoir si une image est noire
 * 
 * @param image image à vérifier
 * @return vrai si l'image est noire et faux sinon
 */
bool EstNoire(image I){
    if(I == NULL)
        return true;
    if(I->toutnoir)
        return true;
    if(!I->toutnoir)
        return false;
    bool tmp = true;
    for(int i=0; i<4; i++)
        tmp &= EstNoire(I->fils[i]);
    return tmp;
}

/**
 * @brief fonction qui fait la copie profonde de I
 * 
 * @param image l'image que l'on doit copier
 * @return un copie profonde du paramètre
*/
image Copie(image I){
    if(I!=NULL){
        if(I->toutnoir)
            return Construit_Noir();
        if(!I->toutnoir)
            return Construit_Blanc();
        return Construit_Composee(Copie(I->fils[0]),Copie(I->fils[1]),Copie(I->fils[2]),Copie(I->fils[3]));
    }
}

/**
 * @brief fonction qui libère la mémoire de l'image
 * 
 * @param image l'image que l'on doit free
*/
void RendMemoire(image I){
    if(I!=NULL){
        for(int i=0; i<4; i++)
            RendMemoire(I->fils[i]);
        free(I);
    }
}

//ATTENTION OPTIMISATION CATASTROPHIQUE
/**
 * @brief fonction qui colorie la diagonale d'une image blanche en noire avec une profondeur de p
 * 
 * @param int profondeur de la diagonale
 * @return l'image avec la diagonale
 */
image Diagonale(int p){
    if(p==0)
        return Construit_Noir();
    image I = Construit_Blanc();
    I->fils[0] = Diagonale(p-1);
    I->fils[3] = Diagonale(p-1);
    I->fils[1] = Construit_Blanc();
    I->fils[2] = Construit_Blanc();
}

/**
 * @brief fonction qui permet de tourner une image d'un quart de tour
 * 
 * @param image image à tourner
 * @return nouvelle image
 */
image QuartDeTour(image I){
    if(!(EstBlanche(I) || EstNoire(I))){
        image tmp;
        for(int i=0; i<4; i++)
            I->fils[i] = QuartDeTour(I->fils[i]);
        tmp = I->fils[0];
        I->fils[0] = I->fils[2];
        I->fils[2] = I->fils[3];
        I->fils[3] = I->fils[1];
        I->fils[1] = tmp;
    }
    return I;
}

/**
 * @brief fonction qui renvoie le négatif de l'image donnée en paramètre
 * 
 * @param image image à transformer
 * @return nouvelle image
 */
image Negatif(image I){
    if(I == NULL)
        return NULL;
    if(EstBlanche(I))
        return Construit_Noir();
    if(EstNoire(I))
        return Construit_Blanc();
    for (int i=0; i<4; i++)
        I->fils[i] = Negatif(I->fils[i]);
    return I;
}

/**
 * @brief fonction qui simplifie le coloriage d'une image
 * 
 * @param image image à simplifier
 * @param int profondeur que l'on doit simplifier
 * @return nouvelle image simplifier
 */
image SimplifieProfP(image I, int p){
    if(I == NULL)
        return NULL;
    if(EstBlanche(I) && p==0)
        return Construit_Blanc();
    if(EstNoire(I) && p==0)
        return Construit_Noir();
    for (int i=0; i<4 && p>0; i++)
        I->fils[i] = SimplifieProfP(I->fils[i],p-1);
    return I;
}



int main(void){
    return EXIT_SUCCESS;
}