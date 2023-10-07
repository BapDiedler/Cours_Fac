#ifndef WORLD_H
#define WORLD_H

typedef struct _sWorld
{
    bool menu;
    bool terminer;
    _tAstraunot * perso;
    _tPavage * pavages;
    char** tab;
} _tWorld;

/// @brief fonction qui initialise le monde du joueur
/// @param nomFichierAstro 
/// @param nomFichierPav 
/// @param nomFichierTerrain 
/// @param world 
/// @param renderer 
/// @param tailleWc 
/// @param tailleHc 
/// @param tailleW 
/// @param tailleH 
/// @param nbLignes 
/// @param nbColonnes 
void initWorld(char* nomFichierAstro, char* nomFichierPav, char* nomFichierTerrain, _tWorld* world, SDL_Renderer* renderer, int * tailleWc, int * tailleHc, int * tailleW, int * tailleH, int * nbLignes, int * nbColonnes);

/// @brief déplacement du personnage vers le bas
/// @param perso 
/// @param tab 
/// @param nbLignes 
/// @param nbColonnes 
/// @return 
bool deplacementBas(_tWorld* world, int nbLignes, int nbColonnes);

/// @brief déplacement du personnage vers la gauche
/// @param perso 
/// @param pavages 
/// @param tab 
/// @param imagePersonnage 
/// @param nbLignes 
/// @param nbColonnes 
void deplacementGauche(_tWorld* world, SDL_Rect * imagePersonnage, int nbLignes, int nbColonnes);

/// @brief déplacement du personnage vers la droite
/// @param perso 
/// @param pavages 
/// @param tab 
/// @param imagePersonnage 
/// @param nbLignes 
/// @param nbColonnes 
void deplacementDroit(_tWorld * world, SDL_Rect * imagePersonnage, int nbLignes, int nbColonnes);


#endif