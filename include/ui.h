#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief Draws text at a specified position.
 *
 * Renders the given text using the specified font and color,
 * with its top-left position at the provided coordinates.
 *
 * @param renderer Pointer to the SDL renderer used for drawing.
 * @param font Pointer to the TTF font used to render the text.
 * @param text Null-terminated string to render.
 * @param color SDL color to apply to the text.
 * @param x Horizontal coordinate of the text's left edge.
 * @param y Vertical coordinate of the text's top edge.
 *
 * @note The renderer and font must be valid, and SDL_ttf must
 *       be initialized before calling this function.
 */
void draw_text(SDL_Renderer *renderer, TTF_Font *font,
               const char *text, SDL_Color color, int x, int y);

/**
 * @brief Draws text horizontally centered at a specified position.
 *
 * Renders the given text so that its horizontal center aligns
 * with @p center_x. The @p y coordinate specifies the top edge
 * of the rendered text.
 *
 * @param renderer Pointer to the SDL renderer used for drawing.
 * @param font Pointer to the TTF font used to render the text.
 * @param text Null-terminated string to render.
 * @param color SDL color to apply to the text.
 * @param center_x Horizontal coordinate of the text's center.
 * @param y Vertical coordinate of the text's top edge.
 *
 * @note The renderer and font must be valid, and SDL_ttf must
 *       be initialized before calling this function.
 */
void draw_centered_text(SDL_Renderer *renderer, TTF_Font *font,
                        const char *text, SDL_Color color,
                        int center_x, int y);

/**
 * @brief Draws a placeholder screen with a title.
 *
 * Renders a placeholder UI screen using the supplied regular
 * and title fonts. The exact layout and appearance depend on
 * the implementation of this function.
 *
 * @param renderer Pointer to the SDL renderer used for drawing.
 * @param font Pointer to the regular font used for placeholder text.
 * @param title_font Pointer to the font used for the title.
 * @param title Null-terminated string containing the placeholder title.
 *
 * @note The renderer and fonts must be valid, and SDL_ttf must
 *       be initialized before calling this function.
 */
void draw_placeholder(SDL_Renderer *renderer, TTF_Font *font,
                      TTF_Font *title_font, const char *title);

#endif /* UI_H */

