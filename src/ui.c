#include "ui.h"

void draw_text(SDL_Renderer *renderer, TTF_Font *font,
               const char *text, SDL_Color color, int x, int y)
{
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface)
        return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture) {
        SDL_Rect dst = { x, y, surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_DestroyTexture(texture);
    }

    SDL_FreeSurface(surface);
}

void draw_centered_text(SDL_Renderer *renderer, TTF_Font *font,
                        const char *text, SDL_Color color,
                        int center_x, int y)
{
    int width, height;

    if (TTF_SizeUTF8(font, text, &width, &height) == 0) {
        draw_text(renderer, font, text, color,
                  center_x - width / 2, y);
    }
}

void draw_placeholder(SDL_Renderer *renderer, TTF_Font *font,
                      TTF_Font *title_font, const char *title)
{
    const SDL_Color gold = { 184, 134, 11, 255 };
    const SDL_Color text = { 245, 239, 220, 255 };

    draw_centered_text(renderer, title_font, title, gold, 400, 220);
    draw_centered_text(renderer, font, "Press ESC to return",
                       text, 400, 310);
}
