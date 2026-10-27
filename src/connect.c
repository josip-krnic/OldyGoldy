#include "connect/connect.h"
#include "ui.h"

void connect_draw(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *title_font)
{
    draw_placeholder(renderer, font, title_font, "Connect");
}
