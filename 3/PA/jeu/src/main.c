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

/**
 * @brief fonction qui libère l'espace memoir
 * @param SDL_Texture * fond
 * @param SDL_Texture * texture
 * @param SDL_Renderer * renderer
 * @param SDL_Window * window
*/
void liberer(_tWorld * world, SDL_Renderer* renderer, SDL_Window* window){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        free(world);
    }


//___MAIN_PART___
int main(void){

    SDL_Event evenements; // Événements liés à la fenêtre
    SDL_MouseButtonEvent souris;//gestion de la souris
    SDL_Window * window = SDL_CreateWindow("Terrain",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR_FENETRE*32,HAUTEUR_FENETRE*32,SDL_WINDOW_RESIZABLE);
    if(window == NULL){ // En cas d’erreur
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer * renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){ // En cas d’erreur
        printf("Erreur de la creation du renderer: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    //initialisation du monde
    int nbLignes;//nombre de ligne dans le terrain
    int nbColonnes;//nombre de colonnes dans le terrain
    int tailleWc, tailleHc;//taille en largeur et en hauteur du personnage
    int tailleW, tailleH ;//taille en hauteur et en largeur d'un bloc
    _tWorld * world = malloc(sizeof(_tWorld));
    initWorld("../ressource/sprites.bmp","../ressource/pavage.bmp","../ressource/terrain.txt",world,renderer,&tailleWc,&tailleHc,&tailleW,&tailleH,&nbLignes,&nbColonnes);
    SDL_Rect imagePersonnage = world->perso->SrcR_sprite[0];//image de départ du personnage;

    //gestion du texte d'affichage
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("../ressource/arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    int  texteW , texteH;
    char msg[] = "MENU";
    TTF_SizeText(font, msg, &texteW, &texteH);
    SDL_Texture* texte = charger_texte(msg,renderer,font,color);
    SDL_Rect text_pos; // Position du texte
    text_pos.x = LARGEUR_FENETRE*32-64;
    text_pos.y = 0;
    text_pos.w = 64;
    text_pos.h = 64;

    //message sur l'accueil du jeu
    TTF_Font * accueil = TTF_OpenFont("../ressource/arial.ttf",28);
    int  texteWaccueil, texteHaccueil;
    char * msgAccueil = "ACCUEIL";
    TTF_SizeText(accueil, msg, &texteWaccueil, &texteHaccueil);
    SDL_Texture* texte_accueil = charger_texte(msgAccueil,renderer,accueil,color);
    SDL_Rect text_pos_accueil; // Position du texte
    text_pos_accueil.x = LARGEUR_FENETRE*32/2-64;
    text_pos_accueil.y = HAUTEUR_FENETRE*32/2-64;
    text_pos_accueil.w = 64;
    text_pos_accueil.h = 64;

    //message si le joueur a perdu
    TTF_Font * perdu = TTF_OpenFont("../ressource/arial.ttf",28);
    int  texteWperdu, texteHperdu;
    char * msgPerdu = "PERDU";
    TTF_SizeText(accueil, msg, &texteWperdu, &texteHperdu);
    SDL_Texture* texte_perdu = charger_texte(msgPerdu,renderer,perdu,color);
    SDL_Rect text_pos_perdu; // Position du texte
    text_pos_perdu.x = LARGEUR_FENETRE*32/2-64;
    text_pos_perdu.y = HAUTEUR_FENETRE*32/2-64;
    text_pos_perdu.w = 64;
    text_pos_perdu.h = 64;
    

    // Boucle principale
    while(!world->terminer){
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);

        if(!estVivant(world->perso)){//seulement si le personnage est mort
            //affichage du texte
            SDL_RenderCopy(renderer,texte_perdu,NULL,&text_pos_perdu);
            SDL_RenderPresent(renderer);
            SDL_Delay(2000);
            initAstraunot("../ressource/sprites.bmp",world->perso,renderer,&tailleWc,&tailleHc,nbLignes);
            world->tab = lire_fichier("../ressource/terrain.txt");
            initPavage("../ressource/pavage.bmp",renderer,world->pavages,world->tab,&tailleW,&tailleH);
            world->menu = true;
        }
        else if(!world->menu){//si le personnage est vivant et que l'on n'est pas sur le menu
            if(world->perso->saut){
                if(world->perso->posSaut==0){
                    world->perso->positionY--;
                    world->perso->DestR_sprite.y-=tailleH;
                    world->perso->posSaut++;
                }
                else if(world->perso->posSaut==1){
                    SDL_Delay(100);
                    world->perso->saut^=true;
                    world->perso->posSaut=0;
                    if(imagePersonnage.y==world->perso->SrcR_sprite[0].y){//en cas de collision
                        deplacementDroit(world,&imagePersonnage,nbLignes,nbColonnes);
                    }
                    else if(imagePersonnage.y==world->perso->SrcR_sprite[3].y){//en cas de collision
                        deplacementGauche(world,&imagePersonnage,nbLignes,nbColonnes);
                    }
                }
            }
            //affichage des données du pavage
            afficherPavage(world->pavages,renderer,world->tab);

            //affichage du texte
            SDL_RenderCopy(renderer,texte,NULL,&text_pos);

            //affichage de l'astraunot
            SDL_RenderCopy(renderer, world->perso->texture, &imagePersonnage, &world->perso->DestR_sprite);
            SDL_RenderPresent(renderer);
        }
        else{//si on est sur le menu
            //affichage du texte
            SDL_RenderCopy(renderer,texte_accueil,NULL,&text_pos_accueil);
            SDL_RenderPresent(renderer);
        }


        //gestion des evenements
        SDL_PollEvent( &evenements );
        switch(evenements.type){
            case SDL_QUIT:
                world->terminer = true; break;
            case SDL_KEYDOWN:
                if(!world->menu && estVivant(world->perso)){
                    switch(evenements.key.keysym.sym){
                        case SDLK_ESCAPE:
                        case SDLK_q:
                        world->terminer = true; break;

                        case SDLK_RIGHT:
                            deplacementDroit(world,&imagePersonnage,nbLignes,nbColonnes);
                            do{}
                            while(deplacementBas(world,nbLignes,nbColonnes));
                            break;
                        case SDLK_LEFT:
                            deplacementGauche(world,&imagePersonnage,nbLignes,nbColonnes);
                            do{}
                            while(deplacementBas(world,nbLignes,nbColonnes));
                            break;
                        case SDLK_DOWN:
                            do{}
                            while(deplacementBas(world,nbLignes,nbColonnes));
                            break;
                        case SDLK_UP:
                            if(!world->perso->saut){
                                world->perso->saut^=true;
                            }
                            break;
                        case SDLK_s:
                            ecrire_fichier("../ressource/terrain.txt",world->tab,nbLignes,nbColonnes);
                            break;
                        case SDLK_SPACE:
                            world->menu^=true;
                            break;
                        default:
                            break;
                    }
                }
                else{
                    switch(evenements.key.keysym.sym){
                        case SDLK_SPACE:
                            world->menu^=true;
                            break;
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            world->terminer = true; break;
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN://gestion de la souris pour faire pause et aller au menu
                SDL_GetMouseState(&souris.x,&souris.y);
                switch (evenements.button.button){
                    case SDL_BUTTON_LEFT:
                        if(!world->menu){
                            if(souris.y>0 && souris.y<=64 && souris.x<LARGEUR_FENETRE*32 && souris.x>=LARGEUR_FENETRE*32-64){
                                world->menu^=true;
                            }
                        }
                        else{
                            if(souris.y>HAUTEUR_FENETRE*32/2 && souris.y<=HAUTEUR_FENETRE*32/2 +64 && souris.x<LARGEUR_FENETRE*32/2&& souris.x>=LARGEUR_FENETRE*32/2 -64){
                                world->menu^=true;
                            }
                        }
                        break;
                    default:
                        break;
                }
                break;
        }
    }

    // Quitter SDL
    liberer(world, renderer, window);
    // Fermer la police et quitter SDL_ttf
    SDL_Quit();
    
    return EXIT_SUCCESS;
}