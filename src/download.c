#include "download/download.h"
#include "ui.h"

void download_draw(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *title_font)
{
    draw_placeholder(renderer, font, title_font, "Download");
}
