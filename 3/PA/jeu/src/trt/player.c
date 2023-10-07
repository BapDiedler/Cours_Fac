#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include "player.h"

/**
 * @param char * nomFichier
 * @param _tAstraunot* perso
 * @param SDL_Renderer* renderer
 * @param int * tailleWc
 * @param int * tailleHc
 * @param in tnbLignes
*/
void initAstraunot(char* nomFichier, _tAstraunot* perso, SDL_Renderer* renderer, int * tailleWc, int * tailleHc, int nbLignes){
    //gestion du personnage
    perso->vie = 1;
    perso->positionX = 1;
    perso->positionY = nbLignes-3;
    perso->saut=false;
    perso->posSaut = 0;
    Uint8 r2 = 0, g2 = 255, b2 = 255;
    SDL_Texture* texture = charger_image_transparente(nomFichier, renderer,r2,g2,b2);
    perso->texture = texture;
    SDL_QueryTexture(perso->texture,NULL,NULL,tailleWc,tailleHc);
    *tailleWc/=3;
    *tailleHc/=2;
    for(int k=0; k<6; k++){
        perso->SrcR_sprite[k].x= k>2 ? (k-3)*(*tailleWc) : k*(*tailleWc);
        perso->SrcR_sprite[k].y= k>2 ? *tailleHc : 0;
        perso->SrcR_sprite[k].w = *tailleWc;
        perso->SrcR_sprite[k].h = *tailleHc;
    } 
    perso->DestR_sprite.x = perso->positionX*32;
    perso->DestR_sprite.y = perso->positionY*32;
    perso->DestR_sprite.w = 32; // Largeur du sprite
    perso->DestR_sprite.h = 32; // Hauteur du sprite
}

/**
 * @brief fonction qui nous dit si l'astraunot est en vie
 * @param _tAstraunot * perso
*/
bool estVivant(_tAstraunot * perso){
    if(perso->vie==0){
        return false;
    }
    return true;
}

/**
 * @param SDL_Rect qui represente l'astraunot
 * @return vrai si le chat est au bord du terrain 
*/
bool collisionRight(_tAstraunot * perso, int nbColonnes){
    return perso->positionX == nbColonnes-1;
}
/**
 * @param SDL_Rect qui represente l'astraunot
 * @return vrai si le chat est au bord du terrain 
*/
bool collisionLeft(_tAstraunot * perso){
    return perso->positionX == 0;
}
/**
 * @param SDL_Rect qui represente l'astraunot
 * @return vrai si le chat est au bord du terrain 
*/
bool collisionDown(_tAstraunot * perso,int nbLignes){
    return perso->positionY==nbLignes-2;
}

/// @brief fonction qui gère le collision entre l'astraunot et les blocs
/// @param pavages 
/// @param perso 
/// @return 
bool collisionBlocLeft(_tAstraunot*  perso, char** tab, int hauteur, int largeur){
    char c;
    for(int i=0; i<hauteur; i++){
        for(int j=0; j<largeur; j++){
            c=tab[i][j]-48;
            if(c==3){
                if(j==perso->positionX+1 && i==perso->positionY){
                    perso->vie--;
                    return false;
                }
            }
            if(c==2){//si le bloc est une piece
                if(j==perso->positionX+1 && i==perso->positionY){
                    tab[i][j]=' ';
                    return false;
                }
            }
            if(c>=0 && c<10){
                if(j==perso->positionX+1){
                    if(i==perso->positionY)
                        return true;
                }
            }
        }
    }
    return false;
}
/// @brief fonction qui gère le collision entre l'astraunot et les blocs
/// @param pavages 
/// @param perso 
/// @return 
bool collisionBlocRight( _tAstraunot*  perso, char** tab, int hauteur, int largeur){
    char c;
    for(int i=0; i<hauteur; i++){
        for(int j=0; j<largeur; j++){
            c=tab[i][j]-48;
            if(c==3){
                if(j==perso->positionX-1 && i==perso->positionY){
                    perso->vie--;
                    return false;
                }
            }
            if(c==2){//si le bloc est une piece
                if(j==perso->positionX-1 && i==perso->positionY){
                    tab[i][j]=' ';
                    return false;
                }
            }
            if(c>=0 && c<10){
                if(j==perso->positionX-1 && i==perso->positionY){
                    return true;
                }
            }
        }
    }
    return false;
}
/// @brief fonction qui gère le collision entre l'astraunot et les blocs
/// @param pavages 
/// @param perso 
/// @return 
bool collisionBlocUp( _tAstraunot*  perso, char** tab, int hauteur, int largeur){
    char c;
    for(int i=0; i<hauteur; i++){
        for(int j=0; j<largeur; j++){
            c=tab[i][j]-48;
            if(c==3){
                if(j==perso->positionX && i==perso->positionY-1){
                    perso->vie--;
                    return false;
                }
            }
            if(c==2){//si le bloc est une piece
                if(j==perso->positionX && i==perso->positionY-1){
                    tab[i][j]=' ';
                    return false;
                }
            }
            if(c>=0 && c<10){//si le bloc n'est pas une piece
                if(j==perso->positionX && i==perso->positionY-1){
                    return true;
                }
            }
        }
    }
    return false;
}
/// @brief fonction qui gère le collision entre l'astraunot et les blocs
/// @param pavages 
/// @param perso 
/// @return 
bool collisionBlocDown( _tAstraunot*  perso, char** tab, int hauteur, int largeur){
    char c;
    for(int i=0; i<hauteur; i++){
        for(int j=0; j<largeur; j++){
            c=tab[i][j]-48;
            if(c==3){//si le perso est sur un piege
                if(j==perso->positionX && i==perso->positionY+1){
                    perso->vie--;
                    return false;
                }
            }
            if(c==2){//si le bloc est une piece
                if(j==perso->positionX && i==perso->positionY+1){
                    tab[i][j]=' ';
                    return false;
                }
            }
            if(c>=0 && c<10){
                if(j==perso->positionX && i==perso->positionY+1){
                    return true;
                }
            }
        }
    }
    return false;
}