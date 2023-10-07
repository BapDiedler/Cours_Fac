#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fonctions_fichiers.h"
#include "fonctions_SDL.h"

/**
 * @brief fonction qui regarde si le chat est en collision avec un mur
 * @param char ** tab
 * @param int n
 * @param int m
 * @param SDL_Rect chat
*/
bool collision(char ** tab, int tailleW, int tailleH, SDL_Rect chat){
    int i = 0 , j = 0;
    i = (chat.y)/tailleH;
    j = (chat.x+chat.w/2)/tailleW;
    if(tab[i][j]=='4'){
        return true;
    }
    return false;
}

/**
 * @brief fonction qui libère l'espace memoir
 * @param SDL_Texture * fond
 * @param SDL_Texture * chats
 * @param SDL_Renderer * renderer
 * @param SDL_Window * window
*/
void liberer(SDL_Texture * fond, SDL_Texture * chats, SDL_Renderer * renderer, SDL_Window * window){
        SDL_DestroyTexture(fond);
        SDL_DestroyTexture(chats);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

/**
 * @brief fonction qui modifie le terrain en fonction de tab
 * @param int tailleW
 * @param int tailleH
 * @param char ** tab
 * @param SDL_Rect * SrcR_pavet
*/
void updatePavage(int tailleW, int tailleH, char ** tab, SDL_Rect * SrcR_pavet){
    int nbLignes , nbColonnes;
    taille_fichier("ressource/terrain.txt",&nbLignes, &nbColonnes);//dimension du terrain
    int k = 0;
    int val;
    for(int i=0; i<(nbColonnes); i++){
        for(int j=0; j<(nbLignes); j++){
            val = tab[j][i]-48;
            if(tab[j][i]==' '){
                tab[j][i]='0';
            }
            if(val<160 && val>=0){
                SrcR_pavet[k].x = val*tailleW;
                SrcR_pavet[k].y = 0;
                SrcR_pavet[k].w = tailleW;
                SrcR_pavet[k].h = tailleH;
                k++;
            }
        }
    }
}


/*void initPavage(SDL_Renderer * renderer, int tailleW, int tailleH){
    SDL_Rect SrcR_pavet[(nbLignes)*(nbColonnes)];
    updatePavage(tailleW, tailleH, tab, SrcR_pavet);
    SDL_Rect DestR_pavet[(nbLignes)*(nbColonnes)];
    int cpt = 0;
    for(int i=0; i<(nbColonnes); i++){
        for(int j=0; j<(nbLignes); j++){
            DestR_pavet[cpt].x = i*(tailleFondW/nbColonnes);
            DestR_pavet[cpt].y = j*(tailleFondH/nbLignes);
            DestR_pavet[cpt].w = (tailleFondW/nbColonnes); // Largeur du sprite
            DestR_pavet[cpt].h = (tailleFondH/nbLignes); // Hauteur du sprite
            cpt++;
        }
    }
}*/

int main(void){
    int nbLignes = 0;
    int nbColonnes = 0;
    bool terminer = false;
    SDL_Event evenements; // Événements liés à la fenêtre
    taille_fichier("ressource/terrain.txt",&nbLignes, &nbColonnes);//dimension du terrain
    char** tab = lire_fichier("ressource/terrain.txt");
    SDL_Window * window = SDL_CreateWindow("Terrain",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1408,641,SDL_WINDOW_RESIZABLE);
    if(window == NULL){ // En cas d’erreur
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Renderer * renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    //gestion du fond
    int tailleFondW, tailleFondH;
    SDL_Texture * fond = charger_image("ressource/fond.bmp",renderer);
    if(fond == NULL){ // En cas d’erreur
        printf("Erreur de la creation du fond d'écran: %s",SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_QueryTexture(fond,NULL,NULL,&tailleFondW,&tailleFondH);

    //gestion des pavets
    SDL_Texture * pavages = charger_image("ressource/pavage.bmp",renderer);
    int tailleW, tailleH ;
    SDL_Rect SrcR_pavet[(nbLignes)*(nbColonnes)];
    updatePavage(tailleW, tailleH, tab, SrcR_pavet);
    SDL_Rect DestR_pavet[(nbLignes)*(nbColonnes)];
    int cpt = 0;
    for(int i=0; i<(nbColonnes); i++){
        for(int j=0; j<(nbLignes); j++){
            DestR_pavet[cpt].x = i*(tailleFondW/nbColonnes);
            DestR_pavet[cpt].y = j*(tailleFondH/nbLignes);
            DestR_pavet[cpt].w = (tailleFondW/nbColonnes); // Largeur du sprite
            DestR_pavet[cpt].h = (tailleFondH/nbLignes); // Hauteur du sprite
            cpt++;
        }
    }
    SDL_QueryTexture(pavages,NULL,NULL,&tailleW,&tailleH);
    tailleH/=10;
    tailleW/=16;

    


    //gestion du personnage
    Uint8 r2 = 0, g2 = 255, b2 = 255;
    SDL_Texture* chats = charger_image_transparente("ressource/sprites.bmp", renderer,r2,g2,b2);
    int tailleWC = 285/3 ,tailleHC = 250/2;
    SDL_Rect SrcR_sprite[6];
    for(int k=0; k<6; k++){
        SrcR_sprite[k].x= k>2 ? (k-3)*tailleWC : k*tailleWC;
        SrcR_sprite[k].y= k>2 ? tailleHC : 0;
        SrcR_sprite[k].w = tailleWC;
        SrcR_sprite[k].h = tailleHC;
    } 
    SDL_Rect DestR_sprite;
    DestR_sprite.x = 0;
    DestR_sprite.y = 0;
    DestR_sprite.w = (tailleFondW/nbColonnes); // Largeur du sprite
    DestR_sprite.h = (tailleFondH/nbLignes); // Hauteur du sprite

    SDL_Rect deplacementDroiteSrc = SrcR_sprite[0];


    //initialisation de la souris
    SDL_MouseButtonEvent souris;
    souris.x = 0;
    souris.y = 0;

    // Boucle principale
    while(!terminer){

        //update des données du pavage
        updatePavage(tailleW, tailleH, tab, SrcR_pavet);

        SDL_RenderClear(renderer);
        //SDL_RenderCopy(renderer, fond, NULL, NULL);
        
        //affichage des données du pavage
        for(int k=0; k<(nbColonnes)*(nbLignes); k++){
            SDL_RenderCopy(renderer, pavages, &SrcR_pavet[k], &DestR_pavet[k]);
        }
        //affichage du chat
        SDL_RenderCopy(renderer, chats, &deplacementDroiteSrc, &DestR_sprite);
    
        SDL_PollEvent( &evenements );
        SDL_RenderPresent(renderer);

        //gestion des evenements
        SDL_PollEvent( &evenements );
        switch(evenements.type){
            case SDL_QUIT:
                terminer = true; break;
            case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                    terminer = true; break;

                    case SDLK_RIGHT:
                        DestR_sprite.x+=tailleW;
                        if(!collision(tab,tailleFondW/nbColonnes,tailleFondH/nbLignes,DestR_sprite)){
                            DestR_sprite.x-=tailleW;
                            if( !((DestR_sprite.x+DestR_sprite.w/2 )>tailleFondW/2)){
                                DestR_sprite.x+=tailleW;
                                DestR_sprite.x+=tailleW;
                                if(deplacementDroiteSrc.x == 0){
                                    deplacementDroiteSrc = SrcR_sprite[1];
                                }
                                else if(deplacementDroiteSrc.x == tailleWC){
                                    deplacementDroiteSrc = SrcR_sprite[2];
                                }
                                else{
                                    deplacementDroiteSrc = SrcR_sprite[0];
                                }
                            }
                            else{

                            }
                        }
                        else{
                            DestR_sprite.x-=tailleW;
                        }
                        break;
                    case SDLK_LEFT:
                        DestR_sprite.x-=tailleW;
                        if(!collision(tab,tailleFondW/nbColonnes,tailleFondH/nbLignes,DestR_sprite)){
                            if(deplacementDroiteSrc.x == 0){
                                deplacementDroiteSrc = SrcR_sprite[4];
                            }
                            else if(deplacementDroiteSrc.x == tailleWC){
                                deplacementDroiteSrc = SrcR_sprite[5];
                            }
                            else{
                                deplacementDroiteSrc = SrcR_sprite[3];
                            }
                        }
                        else{
                            DestR_sprite.x+=tailleW;
                        }
                        break;
                    case SDLK_UP:
                        DestR_sprite.y-=tailleH;
                        if(collision(tab,tailleFondW/nbColonnes,tailleFondH/nbLignes,DestR_sprite)){
                            DestR_sprite.y+=tailleH;
                        }
                        break;
                    case SDLK_DOWN:
                        DestR_sprite.y+=tailleH;
                        if(collision(tab,tailleFondW/nbColonnes,tailleFondH/nbLignes,DestR_sprite)){
                            DestR_sprite.y-=tailleH;
                        }
                        break;
                    case SDLK_s:
                        ecrire_fichier("ressource/terrain.txt",tab,nbLignes,nbColonnes);
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&souris.x,&souris.y);
                switch (evenements.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if(tab[souris.y/(tailleFondH/nbLignes)][souris.x/(tailleFondW/nbColonnes)]=='0')
                    tab[souris.y/(tailleFondH/nbLignes)][souris.x/(tailleFondW/nbColonnes)]='4';
                    break;
                case SDL_BUTTON_RIGHT:
                    if(tab[souris.y/(tailleFondH/nbLignes)][souris.x/(tailleFondW/nbColonnes)]=='4')
                        tab[souris.y/(tailleFondH/nbLignes)][souris.x/(tailleFondW/nbColonnes)]='0';
                    break;
                
                default:
                    break;
                }
                break;
        }
    }

    // Quitter SDL
    liberer(fond, chats, renderer, window);
    // Fermer la police et quitter SDL_ttf
    SDL_Quit();
    
    return EXIT_SUCCESS;
}