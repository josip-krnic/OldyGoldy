#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void download_draw(SDL_Renderer *renderer, TTF_Font *font,
                   TTF_Font *title_font);

#endif
