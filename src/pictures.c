#include "pictures/pictures.h"
#include "ui.h"

void pictures_draw(SDL_Renderer *renderer, TTF_Font *font,
                   TTF_Font *title_font)
{
    draw_placeholder(renderer, font, title_font, "Pictures");
}
