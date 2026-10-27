
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#include "screen.h"
#include "menu.h"
#include "games/games.h"
#include "music/music.h"
#include "pictures/pictures.h"
#include "download/download.h"
#include "connect/connect.h"
#include "games/native_games.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static TTF_Font *font = NULL;
static TTF_Font *title_font = NULL;

static const SDL_Color BG_COLOR = { 25, 24, 30, 255 };

static bool init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() != 0) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "oldy goldy",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
        return false;
    }

    font = TTF_OpenFont("/home/josip/Desktop/oldygoldy/OldyGoldy/fonts/DejaVuSans.ttf", 24);
    title_font = TTF_OpenFont("/home/josip/Desktop/oldygoldy/OldyGoldy/fonts/DejaVuSans.ttf", 44);

    if (!font || !title_font) {
        fprintf(stderr, "Font loading failed: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

static void cleanup(void)
{
    if (title_font) TTF_CloseFont(title_font);
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}

static void draw_screen(Screen current_screen)
{
    switch (current_screen) {
        case SCREEN_MENU:
            menu_draw(renderer, font, title_font);
            break;

        case SCREEN_GAMES:
            games_draw(renderer, font, title_font);
            break;

        case SCREEN_MUSIC:
            music_draw(renderer, font, title_font);
            break;

        case SCREEN_PICTURES:
            pictures_draw(renderer, font, title_font);
            break;

        case SCREEN_DOWNLOAD:
            download_draw(renderer, font, title_font);
            break;

        case SCREEN_CONNECT:
            connect_draw(renderer, font, title_font);
            break;

        case SCREEN_NATIVE_GAMES:
            native_games_draw(renderer, font, title_font);
            break;
    }
}

int main(void)
{
    if (!init()) {
        cleanup();
        return 1;
    }

    bool running = true;
    Screen current_screen = SCREEN_MENU;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN &&
                       event.key.keysym.sym == SDLK_ESCAPE) {
                if (current_screen == SCREEN_MENU)
                    running = false;
                else
                    current_screen = SCREEN_MENU;
            } else if (current_screen == SCREEN_MENU) {
                current_screen = menu_handle_event(&event);
            } else if (current_screen == SCREEN_GAMES) {
                current_screen = games_handle_event(&event);
            } else if (current_screen == SCREEN_GAMES) {
                current_screen = games_handle_event(&event);
            } else if (current_screen == SCREEN_NATIVE_GAMES) {
                current_screen = native_games_handle_event(&event);
            }
        }

        SDL_SetRenderDrawColor(
            renderer,
            BG_COLOR.r, BG_COLOR.g, BG_COLOR.b, BG_COLOR.a
        );

        SDL_RenderClear(renderer);
        draw_screen(current_screen);
        SDL_RenderPresent(renderer);
    }

    cleanup();
    return 0;
}
