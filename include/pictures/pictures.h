#ifndef PICTURES_H
#define PICTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief Draws the pictures screen.
 *
 * Renders the pictures interface using the specified SDL renderer,
 * regular font, and title font.
 *
 * @param renderer Pointer to the SDL renderer used for drawing.
 * @param font Pointer to the font used for regular text.
 * @param title_font Pointer to the font used for the screen title.
 *
 * @note The renderer and fonts must be valid, and SDL_ttf must
 *       be initialized before calling this function.
 */
void pictures_draw(SDL_Renderer *renderer, TTF_Font *font,
                   TTF_Font *title_font);

#endif /* PICTURES_H */
