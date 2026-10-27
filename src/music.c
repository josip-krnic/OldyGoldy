#include "music/music.h"
#include "ui.h"

void music_draw(SDL_Renderer *renderer, TTF_Font *font,
                TTF_Font *title_font)
{
    draw_placeholder(renderer, font, title_font, "Music");
}
