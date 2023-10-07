#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include "pavage.h"


/// @brief initPavage initialise le fond de la fenêtre en fonctino du tableau
/// @param nomFichier 
/// @param renderer 
/// @param pavages 
/// @param tab 
/// @param tailleW 
/// @param tailleH 
void initPavage(char * nomFichier, SDL_Renderer * renderer, _tPavage * pavages, char ** tab, int * tailleW, int * tailleH){
    pavages->pavages = charger_image(nomFichier,renderer);
    pavages->posEcran = 0;
    int cpt = 0;
    for(int i=0; i<LARGEUR_FENETRE; i++){
        for(int j=0; j<HAUTEUR_FENETRE; j++){
            pavages->DestR_pavet[cpt].x = i*32;
            pavages->DestR_pavet[cpt].y = j*32;
            pavages->DestR_pavet[cpt].w = 32; // Largeur du sprite
            pavages->DestR_pavet[cpt].h = 32; // Hauteur du sprite
            cpt++;
        }
    }
    SDL_QueryTexture(pavages->pavages,NULL,NULL,tailleW,tailleH);
    *tailleW/=16;
    *tailleH/=10;
    updatePavage(tab,pavages);
}

/**
 * @brief fonction qui modifie le terrain en fonction de tab
 * @param int tailleW
 * @param int tailleH
 * @param char ** tab
 * @param SDL_Rect * SrcR_pavet
*/
void updatePavage(char ** tab, _tPavage * pavages){
    int nbLignes , nbColonnes;
    taille_fichier("../ressource/terrain.txt",&nbLignes, &nbColonnes);//dimension du terrain
    int k = 0;
    int x = pavages->posEcran;
    int tailleW = pavages->DestR_pavet->w;
    int tailleH = pavages->DestR_pavet->h;
    int val;
    if(x<nbColonnes){
        for(int i=x; i<LARGEUR_FENETRE+x; i++){
            for(int j=0; j<HAUTEUR_FENETRE; j++){
                if(tab[j][i]==' '){//en cas d'absence de bloc
                    pavages->SrcR_pavet[k].x = 0;
                    pavages->SrcR_pavet[k].y = 0;
                    pavages->SrcR_pavet[k].w = 0;
                    pavages->SrcR_pavet[k].h = 0;
                }
                val = tab[j][i]-48;
                if(val<160 && val>=0){
                    pavages->SrcR_pavet[k].x = val*tailleW;
                    pavages->SrcR_pavet[k].y = 0;
                    pavages->SrcR_pavet[k].w = tailleW;
                    pavages->SrcR_pavet[k].h = tailleH;
                }
                k++;
            }
        }
    }
}

/// @brief la fonction affiche le pavage sur le renderer
/// @param pavages 
/// @param renderer 
/// @param tab 
void afficherPavage(_tPavage * pavages, SDL_Renderer * renderer, char** tab){
    updatePavage(tab, pavages);
        for(int k=0; k<(LARGEUR_FENETRE*HAUTEUR_FENETRE); k++){
            SDL_RenderCopy(renderer, pavages->pavages, &pavages->SrcR_pavet[k], &pavages->DestR_pavet[k]);
        }
}