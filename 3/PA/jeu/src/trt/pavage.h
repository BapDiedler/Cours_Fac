#ifndef PAVAGE_H
#define PAVAGE_H

#define LARGEUR_FENETRE 20
#define HAUTEUR_FENETRE 20

typedef struct _sPavage
    {
        SDL_Rect DestR_pavet[LARGEUR_FENETRE*HAUTEUR_FENETRE];
        SDL_Rect SrcR_pavet[LARGEUR_FENETRE*HAUTEUR_FENETRE];
        SDL_Texture* pavages;
        int posEcran;
    } _tPavage;


/// @brief initPavage initialise le fond de la fenêtre en fonctino du tableau
/// @param nomFichier 
/// @param renderer 
/// @param pavages 
/// @param tab 
/// @param tailleW 
/// @param tailleH 
void initPavage(char * nomFichier, SDL_Renderer * renderer, _tPavage * pavages, char ** tab, int * tailleW, int * tailleH);

/**
 * @brief fonction qui modifie le terrain en fonction de tab
 * @param int tailleW
 * @param int tailleH
 * @param char ** tab
 * @param SDL_Rect * SrcR_pavet
*/
void updatePavage(char ** tab, _tPavage * pavages);

/// @brief la fonction affiche le pavage sur le renderer
/// @param pavages 
/// @param renderer 
/// @param tab 
void afficherPavage(_tPavage * pavages, SDL_Renderer * renderer, char** tab);

#endif