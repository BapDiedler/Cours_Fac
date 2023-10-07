//executer le code : gcc main.c -o main $(sdl2-config --cflags --libs)

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    SDL_Window * window = NULL;//initialisation de la fenetre
    SDL_Renderer * renderer = NULL;//initialisation du renderer
    SDL_Texture *texture = NULL;//initialisation d'une texture
    SDL_Surface *surface = NULL;//initialisation d'une surface
    SDL_Event event;//initialisation d'un variable pour gerer les events
    SDL_bool quit = SDL_FALSE;//variable qui nous dit si l'on quitte la boucle ou non
    SDL_Rect rect1 = {300, 300, 300, 300};
    SDL_Rect rect2 = {100, 100, 100, 100}, dst = {0, 0, 0, 0};
    SDL_Color rouge = {255, 0, 100, 255}, bleuClaire = {0, 255, 255, 255};//initialisation des couleurs rouge et bleu
    int statut = EXIT_FAILURE;

    if(SDL_Init(SDL_INIT_VIDEO)){//initalisation de la SDL video
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);//creation d'un fenetre
    if(window == NULL){//si la fenetre ne s'est pas ouverte
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//creation du renderer
    if(NULL == renderer){//si le renderer ne s'est pas cree
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        goto Quit;
    }

    surface = SDL_CreateRGBSurface(0, 640, 480, 32, 0, 0, 0, 0);//creation d'une surface
    if(NULL == surface){//si la surface ne s'est pas cree
        fprintf(stderr, "Erreur SDL_CreateRGBSurface : %s", SDL_GetError());
        goto Quit;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 200);//creation d'une texture
    if(NULL == texture){//Si la texture ne c'est pas telechargee
        fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
        goto Quit;
    }

    SDL_SetRenderTarget(renderer, texture);//pour dessiner sur la texture
    SDL_SetRenderDrawColor(renderer, bleuClaire.r, bleuClaire.g, bleuClaire.b, bleuClaire.a);//on applique la couleur
    SDL_RenderFillRect(renderer, &rect1); // on dessine un rctangle bleu sur le renderer
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, rouge.r, rouge.g, rouge.b, rouge.a);//on colorie
    SDL_RenderFillRect(renderer, &rect2); // on dessine un rctangle rouge sur le renderer

    SDL_SetRenderTarget(renderer, NULL); // le renderer est la cible du rendu

    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);//recuperation des dimensions 
    SDL_RenderCopy(renderer, texture, NULL, &dst);//on la copie sur le renderer
    SDL_RenderPresent(renderer);//mise à jour de la fenetre
    SDL_RenderClear(renderer);
    while(!quit){//boucle de jeu
        SDL_WaitEvent(&event);//en attente d'une action de l'utilisateur pour continuer
        if(event.type == SDL_QUIT) quit = SDL_TRUE;
    }
    statut = EXIT_SUCCESS;

Quit://en cas d'erreur
    if(NULL != surface) SDL_FreeSurface(surface);//on supprime la surface
    if(NULL != texture) SDL_DestroyTexture(texture);//on supprime la texture
    if(NULL != renderer) SDL_DestroyRenderer(renderer);//on supprime le renderer
    if(NULL != window) SDL_DestroyWindow(window);//on supprime la fenetre
    SDL_Quit();//on quitte la SDL
    return statut;
}