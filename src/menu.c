#include "menu.h"
#include "ui.h"
#include <stdbool.h>
#include <stddef.h>

#define WINDOW_WIDTH 320
#define BUTTON_WIDTH 130
#define BUTTON_HEIGHT 40
#define BUTTON_GAP 10

static const SDL_Color GOLD = { 184, 134, 11, 255 };
static const SDL_Color BG_BUTTON = { 55, 52, 65, 255 };
static const SDL_Color TEXT_COLOR = { 245, 239, 220, 255 };

typedef struct {
    const char *label;
    SDL_Rect rect;
    Screen target;
} Button;

static Button buttons[] = {
    { "games",    { 100, 10,  BUTTON_WIDTH, BUTTON_HEIGHT }, SCREEN_GAMES },
    { "music",    { 100, 70,  BUTTON_WIDTH, BUTTON_HEIGHT }, SCREEN_MUSIC },
    { "pictures", { 100, 130, BUTTON_WIDTH, BUTTON_HEIGHT }, SCREEN_PICTURES },
    { "download", { 100, 190, BUTTON_WIDTH, BUTTON_HEIGHT }, SCREEN_DOWNLOAD },
    { "connect",  { 100, 240, BUTTON_WIDTH, BUTTON_HEIGHT }, SCREEN_CONNECT }
};

#define BUTTON_COUNT (sizeof(buttons) / sizeof(buttons[0]))

static bool point_in_rect(int x, int y, SDL_Rect rect)
{
    return x >= rect.x && x < rect.x + rect.w &&
           y >= rect.y && y < rect.y + rect.h;
}

void menu_draw(SDL_Renderer *renderer, TTF_Font *font,
               TTF_Font *title_font)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    //draw_centered_text(renderer, title_font, "oldy goldy",
    //                   GOLD, WINDOW_WIDTH / 2, 75);

    for (size_t i = 0; i < BUTTON_COUNT; ++i) {
        Button *button = &buttons[i];

        SDL_Color color = point_in_rect(mouse_x, mouse_y, button->rect)
                          ? GOLD : BG_BUTTON;

        SDL_SetRenderDrawColor(renderer,
                               color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &button->rect);

        SDL_SetRenderDrawColor(renderer, 110, 105, 115, 255);
        SDL_RenderDrawRect(renderer, &button->rect);

        int text_width, text_height;
        if (TTF_SizeUTF8(font, button->label,
                         &text_width, &text_height) == 0) {
            draw_text(renderer, font, button->label, TEXT_COLOR,
                      button->rect.x + (button->rect.w - text_width) / 2,
                      button->rect.y + (button->rect.h - text_height) / 2);
        }
    }
}

Screen menu_handle_event(const SDL_Event *event)
{
    if (event->type != SDL_MOUSEBUTTONDOWN ||
        event->button.button != SDL_BUTTON_LEFT) {
        return SCREEN_MENU;
    }

    int x = event->button.x;
    int y = event->button.y;

    for (size_t i = 0; i < BUTTON_COUNT; ++i) {
        if (point_in_rect(x, y, buttons[i].rect))
            return buttons[i].target;
    }

    return SCREEN_MENU;
}
