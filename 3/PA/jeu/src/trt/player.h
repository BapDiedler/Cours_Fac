#ifndef PLAYER_H
#define PLAYER_H

typedef struct _sAstraunot
    {
        SDL_Rect DestR_sprite;
        SDL_Rect SrcR_sprite[6];
        SDL_Texture* texture;
        int positionX;
        int positionY;
        bool saut;
        int posSaut;
        int vie;
    } _tAstraunot;

    /**
 * @param char * nomFichier
 * @param _tAstraunot* perso
 * @param SDL_Renderer* renderer
 * @param int * tailleWc
 * @param int * tailleHc
 * @param in tnbLignes
*/
void initAstraunot(char* nomFichier, _tAstraunot* perso, SDL_Renderer* renderer, int * tailleWc, int * tailleHc, int nbLignes);

/**
 * @brief fonction qui nous dit si l'astraunot est en vie
 * @param _tAstraunot * perso
*/
bool estVivant(_tAstraunot * perso);

/**
 * @param SDL_Rect qui represente l'astraunot
 * @return vrai si le chat est au bord du terrain 
*/
bool collisionRight(_tAstraunot * perso, int nbColonnes);

/**
 * @param SDL_Rect qui represente l'astraunot
 * @return vrai si le chat est au bord du terrain 
*/
bool collisionLeft(_tAstraunot * perso);

/**
 * @param SDL_Rect qui represente l'astraunot
 * @return vrai si le chat est au bord du terrain 
*/
bool collisionDown(_tAstraunot * perso,int nbLignes);

/// @brief fonction qui gère le collision entre l'astraunot et les blocs
/// @param pavages 
/// @param perso 
/// @return 
bool collisionBlocLeft(_tAstraunot*  perso, char** tab, int hauteur, int largeur);

/// @brief fonction qui gère le collision entre l'astraunot et les blocs
/// @param pavages 
/// @param perso 
/// @return 
bool collisionBlocRight( _tAstraunot*  perso, char** tab, int hauteur, int largeur);

/// @brief fonction qui gère le collision entre l'astraunot et les blocs
/// @param pavages 
/// @param perso 
/// @return 
bool collisionBlocUp( _tAstraunot*  perso, char** tab, int hauteur, int largeur);

/// @brief fonction qui gère le collision entre l'astraunot et les blocs
/// @param pavages 
/// @param perso 
/// @return 
bool collisionBlocDown( _tAstraunot*  perso, char** tab, int hauteur, int largeur);

#endif