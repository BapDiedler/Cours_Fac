#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef FONCTIONS_SDL_H
#define FONCTIONS_SDL_H

/**
 * @brief fonction qui charge une image sur un renderer
 * @param const char* nomfichier
 * @param SDL_Renderer* renderer
 */ 
SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer);

/**
 * @brief rend l'image transparente
 * @param const char* nomfichier
 * @param SDL_Renderer* renderer
 * @param Uint8 r
 * @param Uint8 g
 * @param Uint8 b
 */
SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

/**
 * @brief fonction qui charge un texte sur le renderer
 * @param const char* message
 * @param SDL_Renderer* renderer
 * @param TTF_Font *font
 * @param SDL_Color color
 */
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color);

#endif
