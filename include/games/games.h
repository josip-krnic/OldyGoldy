#ifndef GAMES_H
#define GAMES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"

void games_draw(SDL_Renderer *renderer, TTF_Font *font,
                TTF_Font *title_font);

Screen games_handle_event(const SDL_Event *event);

#endif
