#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"
#include "pavage.h"
#include "player.h"
#include "world.h"


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
void initWorld(char* nomFichierAstro, char* nomFichierPav, char* nomFichierTerrain, _tWorld* world, SDL_Renderer* renderer, int * tailleWc,
                int * tailleHc, int * tailleW, int * tailleH, int * nbLignes, int * nbColonnes){
    world->menu = true; ///le jeu commendce sur le menu
    world->terminer = false;//le jeu commence
    taille_fichier(nomFichierTerrain,nbLignes, nbColonnes);//dimension du terrain
    world->tab = lire_fichier(nomFichierTerrain);
    world->perso = malloc(sizeof(_tAstraunot));
    world->pavages = malloc(sizeof(_tPavage));
    initAstraunot(nomFichierAstro,world->perso,renderer,tailleWc,tailleHc,*nbLignes);//initialisation du personnage
    initPavage(nomFichierPav,renderer,world->pavages,world->tab,tailleW,tailleH);//initialisation du pavage
}

/// @brief déplacement du personnage vers le bas
/// @param perso 
/// @param tab 
/// @param nbLignes 
/// @param nbColonnes 
/// @return 
bool deplacementBas(_tWorld * world, int nbLignes, int nbColonnes){
    if(!collisionDown(world->perso, nbLignes) && !collisionBlocDown(world->perso, world->tab, nbLignes, nbColonnes)){//gravité du jeu
        world->perso->positionY++;
        world->perso->DestR_sprite.y+=world->perso->DestR_sprite.h;
        return true;
    }
    return false;
}

/// @brief déplacement du personnage vers la gauche
/// @param perso 
/// @param pavages 
/// @param tab 
/// @param imagePersonnage 
/// @param nbLignes 
/// @param nbColonnes 
void deplacementGauche(_tWorld * world, SDL_Rect * imagePersonnage, int nbLignes, int nbColonnes){
    if(!(collisionLeft(world->perso) || collisionBlocRight(world->perso, world->tab,nbLignes, nbColonnes))){
        world->perso->positionX--;
        if((world->perso->DestR_sprite.x+world->perso->DestR_sprite.w/2 ) >= LARGEUR_FENETRE*32/2){//si le personnage se trouve au milieu de l'écran
            world->perso->DestR_sprite.x-=world->perso->DestR_sprite.w;
        }
        else if(world->pavages->posEcran!=0){
            world->pavages->posEcran--;
        }
        else{
            world->perso->DestR_sprite.x-=world->perso->DestR_sprite.w;
        }
        //changement des images pour le déplacement
        if(imagePersonnage->x == 0){
            *imagePersonnage = world->perso->SrcR_sprite[4];
        }
        else if(imagePersonnage->x == world->perso->SrcR_sprite->w){
            *imagePersonnage = world->perso->SrcR_sprite[5];
        }
        else{
            *imagePersonnage = world->perso->SrcR_sprite[3];
        }
    }
    while(deplacementBas(world,nbLignes,nbColonnes));
}

/// @brief déplacement du personnage vers la droite
/// @param perso 
/// @param pavages 
/// @param tab 
/// @param imagePersonnage 
/// @param nbLignes 
/// @param nbColonnes 
void deplacementDroit(_tWorld * world, SDL_Rect * imagePersonnage, int nbLignes, int nbColonnes){
    if(!(collisionRight(world->perso, nbColonnes) || (collisionBlocLeft(world->perso,world->tab,nbLignes,nbColonnes)))){//en cas de collision
        world->perso->positionX++;
        if( (world->perso->DestR_sprite.x+world->perso->DestR_sprite.w/2 ) < LARGEUR_FENETRE*32/2 && world->pavages->posEcran<nbColonnes-LARGEUR_FENETRE){//si le personnage se trouve au milieu de l'écran
            world->perso->DestR_sprite.x+=world->perso->DestR_sprite.w;
        }
        else{
            if(world->pavages->posEcran<nbColonnes-LARGEUR_FENETRE)
                world->pavages->posEcran++;
            else{
                world->perso->DestR_sprite.x+=world->perso->DestR_sprite.w; 
            }
        }
        //changement de image pour le déplacement
        if(imagePersonnage->x == 0){
            *imagePersonnage = world->perso->SrcR_sprite[1];
        }
        else if(imagePersonnage->x == world->perso->SrcR_sprite->w){
            *imagePersonnage = world->perso->SrcR_sprite[2];
        }
        else{
            *imagePersonnage = world->perso->SrcR_sprite[0];
        }
    }
    while(deplacementBas(world,nbLignes,nbColonnes));
}