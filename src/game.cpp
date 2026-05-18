#include "game.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>
#include <cstdio>

Game::Game() {}
Game::~Game() {}

void Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return;
    }
    Game::window = SDL_CreateWindow(
            "BURGER",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH,
            HEIGHT,
            SDL_WINDOW_SHOWN|
            SDL_WINDOW_RESIZABLE|
            SDL_WINDOW_ALLOW_HIGHDPI);

    if (Game::window == NULL) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    Game::renderer = SDL_CreateRenderer(Game::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Game::renderer == NULL) {
        printf("Renderer error\n");
        SDL_DestroyWindow(Game::window);
        SDL_Quit();
        return;
    }
    Game::c_gameState = PLAYING;
}

void Game::handleEvents(SDL_Event e) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            Game::running = 0;
        }
        else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_F11) {
                Uint32 flags = SDL_GetWindowFlags(Game::window);
                if (flags & SDL_WINDOW_FULLSCREEN) {
                    SDL_SetWindowFullscreen(window, 0);
                }else {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
            }
            else if (e.key.keysym.sym == SDLK_ESCAPE) {
                switch (Game::c_gameState) {
                    case PLAYING:
                        Game::c_gameState = PAUSED;
                        break;
                    case PAUSED:
                        Game::c_gameState = PLAYING;
                        break;
                    case GAME_OVER:
                        break;
                    case MENU:
                        break;
                }
            }
            else if (e.key.keysym.sym == SDLK_e) {
                Game::running = 0;
            }
        }
    }
}

void Game::render() {
    switch (Game::c_gameState) {
        case MENU:
            break;
        case PLAYING:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            break;
        case PAUSED:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            break;
        case GAME_OVER:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            break;
    }
}

void Game::update() {
}

void Game::clean() {
    SDL_DestroyWindow(Game::window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}
