#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "screen.h"

/**
 * @brief Draws the main menu.
 *
 * Renders the menu interface using the specified SDL renderer,
 * regular font, and title font.
 *
 * @param renderer Pointer to the SDL renderer used for drawing.
 * @param font Pointer to the font used for regular menu text.
 * @param title_font Pointer to the font used for the menu title.
 *
 * @note The renderer and fonts must be valid, and SDL_ttf must
 *       be initialized before calling this function.
 */
void menu_draw(SDL_Renderer *renderer, TTF_Font *font,
               TTF_Font *title_font);

/**
 * @brief Processes an SDL event for the menu.
 *
 * Handles an SDL event and returns the screen corresponding
 * to the resulting menu action or navigation state.
 *
 * @param event Pointer to the SDL event to process.
 *
 * @return The Screen value representing the screen to display
 *         after processing the event.
 *
 * @note The event pointer must refer to a valid SDL_Event.
 */
Screen menu_handle_event(const SDL_Event *event);

#endif /* MENU_H */
