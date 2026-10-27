#include "games/games.h"
#include "games/native_games.h"
#include "ui.h"

#include <stdbool.h>
#include <stddef.h>

#define WINDOW_WIDTH  320
#define BUTTON_WIDTH  160
#define BUTTON_HEIGHT 35
#define BUTTON_GAP    12

typedef enum {
    GAME_NATIVE,
    GAME_GBA,
    GAME_GB,
    GAME_NONE
} GameOption;

typedef struct {
    const char *label;
    SDL_Rect rect;
    GameOption option;
} GameButton;

static const SDL_Color GOLD       = { 184, 134, 11, 255 };
static const SDL_Color BUTTON_BG  = { 55, 52, 65, 255 };
static const SDL_Color TEXT_COLOR = { 245, 239, 220, 255 };

static GameOption selected_game = GAME_NONE;

static GameButton buttons[] = {
    { "native", { 80, 75, BUTTON_WIDTH, BUTTON_HEIGHT }, GAME_NATIVE },
    { "GBA",    { 80, 122, BUTTON_WIDTH, BUTTON_HEIGHT }, GAME_GBA },
    { "GB",     { 80, 169, BUTTON_WIDTH, BUTTON_HEIGHT }, GAME_GB }
};

#define BUTTON_COUNT (sizeof(buttons) / sizeof(buttons[0]))

static bool point_in_rect(int x, int y, SDL_Rect rect)
{
    return x >= rect.x && x < rect.x + rect.w &&
           y >= rect.y && y < rect.y + rect.h;
}

void games_draw(SDL_Renderer *renderer, TTF_Font *font,
                TTF_Font *title_font)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    draw_centered_text(renderer, title_font, "Games",
                       GOLD, WINDOW_WIDTH / 2, 20);

    for (size_t i = 0; i < BUTTON_COUNT; ++i) {
        GameButton *button = &buttons[i];

        bool hovered = point_in_rect(mouse_x, mouse_y, button->rect);
        bool selected = selected_game == button->option;

        SDL_Color color = (hovered || selected) ? GOLD : BUTTON_BG;

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

Screen games_handle_event(const SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN &&
        event->key.keysym.sym == SDLK_ESCAPE) {
        return SCREEN_MENU;
    }

    if (event->type == SDL_MOUSEBUTTONDOWN &&
        event->button.button == SDL_BUTTON_LEFT) {

        int x = event->button.x;
        int y = event->button.y;

        for (size_t i = 0; i < BUTTON_COUNT; ++i) {
            if (point_in_rect(x, y, buttons[i].rect)) {
                if (buttons[i].option == GAME_NATIVE)
                    return SCREEN_NATIVE_GAMES;

                selected_game = buttons[i].option;
                return SCREEN_GAMES;
            }
        }
    }

    return SCREEN_GAMES;
}
