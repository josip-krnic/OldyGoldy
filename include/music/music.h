#ifndef MUSIC_H
#define MUSIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void music_draw(SDL_Renderer *renderer, TTF_Font *font,
                TTF_Font *title_font);

#endif
