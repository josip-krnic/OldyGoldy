#include "games/native_games.h"
#include "ui.h"

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define WINDOW_WIDTH 320
#define LIST_X 20
#define LIST_Y 55
#define ITEM_WIDTH 280
#define ITEM_HEIGHT 30
#define ITEM_GAP 5
#define VISIBLE_ITEMS 5

static const SDL_Color GOLD       = { 184, 134, 11, 255 };
static const SDL_Color BUTTON_BG  = { 55, 52, 65, 255 };
static const SDL_Color TEXT_COLOR = { 245, 239, 220, 255 };

static const char *game_names[] = {
    "tetris",
    "placeholder game 1",
    "placeholder game 2",
    "placeholder game 3"
};

#define GAME_COUNT (sizeof(game_names) / sizeof(game_names[0]))

static int scroll_offset = 0;
static int selected_index = -1;

void native_games_draw(SDL_Renderer *renderer, TTF_Font *font,
                       TTF_Font *title_font)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    draw_centered_text(renderer, title_font, "Native Games",
                       GOLD, WINDOW_WIDTH / 2, 10);

    for (int visible = 0; visible < VISIBLE_ITEMS; ++visible) {
        int index = scroll_offset + visible;

        if (index >= (int)GAME_COUNT)
            break;

        SDL_Rect rect = {
            LIST_X,
            LIST_Y + visible * (ITEM_HEIGHT + ITEM_GAP),
            ITEM_WIDTH,
            ITEM_HEIGHT
        };

        int hovered =
            mouse_x >= rect.x && mouse_x < rect.x + rect.w &&
            mouse_y >= rect.y && mouse_y < rect.y + rect.h;

        SDL_Color color =
            (hovered || selected_index == index) ? GOLD : BUTTON_BG;

        SDL_SetRenderDrawColor(renderer,
                               color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 110, 105, 115, 255);
        SDL_RenderDrawRect(renderer, &rect);

        int text_width, text_height;

        if (TTF_SizeUTF8(font, game_names[index],
                         &text_width, &text_height) == 0) {
            draw_text(renderer, font, game_names[index], TEXT_COLOR,
                      rect.x + 10,
                      rect.y + (rect.h - text_height) / 2);
        }
    }
}

Screen native_games_handle_event(const SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                return SCREEN_GAMES;

            case SDLK_DOWN:
                if (scroll_offset < (int)GAME_COUNT - VISIBLE_ITEMS)
                    ++scroll_offset;
                if (scroll_offset < 0)
                    scroll_offset = 0;
                break;

            case SDLK_UP:
                if (scroll_offset > 0)
                    --scroll_offset;
                break;

            default:
                break;
        }
    }

    if (event->type == SDL_MOUSEWHEEL) {
        if (event->wheel.y < 0 &&
            scroll_offset < (int)GAME_COUNT - VISIBLE_ITEMS)
            ++scroll_offset;

        if (event->wheel.y > 0 && scroll_offset > 0)
            --scroll_offset;

        if (scroll_offset < 0)
            scroll_offset = 0;

        int max_scroll = (int)GAME_COUNT - VISIBLE_ITEMS;
        if (max_scroll < 0)
            max_scroll = 0;
        if (scroll_offset > max_scroll)
            scroll_offset = max_scroll;
    }

    if (event->type == SDL_MOUSEBUTTONDOWN &&
        event->button.button == SDL_BUTTON_LEFT) {

        int x = event->button.x;
        int y = event->button.y;

        for (int visible = 0; visible < VISIBLE_ITEMS; ++visible) {
            int index = scroll_offset + visible;

            if (index >= (int)GAME_COUNT)
                break;

            SDL_Rect rect = {
                LIST_X,
                LIST_Y + visible * (ITEM_HEIGHT + ITEM_GAP),
                ITEM_WIDTH,
                ITEM_HEIGHT
            };

            if (x >= rect.x && x < rect.x + rect.w &&
                y >= rect.y && y < rect.y + rect.h) {
                selected_index = index;
                break;
            }
        }
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            return 1;
        }

        if (pid == 0) {
            // Child process: execute the program
            execl("./games/native/tetris", NULL, (char *)NULL);

            // Reached only if execl() fails
            perror("execl failed");
            _exit(127);
        }

        // Parent process: wait for the child to finish
        int status;

        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid failed");
            return 1;
        }

        if (WIFEXITED(status)) {
            printf("Program finished with exit code %d\n",
                   WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Program terminated by signal %d\n",
                   WTERMSIG(status));
        }
    }

    return SCREEN_NATIVE_GAMES;
}
