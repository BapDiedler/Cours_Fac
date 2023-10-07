#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"

//fonction main
int main(void){
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){ // Initialisation de la SDL
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL){ // En cas d’erreur
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture* fond = charger_image( "ressources/fond.bmp", ecran );

    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* titre = charger_image_transparente("ressources/obj.bmp", ecran,r,g,b);
    SDL_Rect SrcR, DestR;
    int objetW = 640;
    int objetH = 192;
    SrcR.x = 0;
    SrcR.y = 0;
    SrcR.w = objetW;
    SrcR.h = objetH; 
    DestR.x = 350;
    DestR.y = 350;
    DestR.w = objetW/3;
    DestR.h = objetH/3;

    Uint8 r2 = 0, g2 = 255, b2 = 255;
    SDL_Texture* chats = charger_image_transparente("ressources/sprites.bmp", ecran,r2,g2,b2);
    int tailleW = 285/3 ,tailleH = 250/2;
    SDL_Rect SrcR_sprite[6];
    for(int k=0; k<6; k++){
        SrcR_sprite[k].x=0;
        SrcR_sprite[k].y=0;
        SrcR_sprite[k].w = tailleW;
        SrcR_sprite[k].h = tailleH;
    } 
    SDL_Rect DestR_sprite[6];
    for(int i=0; i<6; i++){
        DestR_sprite[i].x = i > 2 ? 60*(i+1)+100 : 60*(i+1);
        DestR_sprite[i].y = i > 2 ? 60 : 120;
        DestR_sprite[i].w = tailleW; // Largeur du sprite
        DestR_sprite[i].h = tailleH; // Hauteur du sprite
    }

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("ressources/arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    int  texteW , texteH;
    char msg[] = "TP sur Makefile et SDL";
    TTF_SizeText(font, msg, &texteW, &texteH);
    SDL_Texture* texte = charger_texte(msg,ecran,font,color);
    printf("%d , %d",texteW,texteH);
    SDL_Rect text_pos; // Position du texte
    text_pos.x = 10;
    text_pos.y = 100;
    text_pos.w = texteW;
    text_pos.h = texteH;

    // Boucle principale
    while(!terminer){
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran, fond, NULL, NULL);
        SDL_RenderCopy(ecran, titre, &SrcR, &DestR);
        for(int j=0; j<6; j++){
            SDL_RenderCopy(ecran, chats, &SrcR_sprite[j], &DestR_sprite[j]);
        }
        SDL_RenderCopy(ecran,texte,NULL,&text_pos);
        SDL_PollEvent( &evenements );
        SDL_RenderPresent(ecran);
        switch(evenements.type){
            case SDL_QUIT:
                terminer = true; break;
            case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                    terminer = true; break;
                }
        //Appliquer la surface du texte sur l’écran
        }
    }
    // Quitter SDL
    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(fenetre);
    SDL_RenderPresent(ecran);
    // Fermer la police et quitter SDL_ttf
    TTF_CloseFont( font );
    TTF_Quit();
    SDL_Quit();
    return 0;
}