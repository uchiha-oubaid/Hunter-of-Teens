#include "game.hpp"
#include "player.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdio>
#include <SDL2/SDL_image.h>

Game::Game() {}
Game::~Game() {}

Player *player = nullptr;
p_movement pMovement;

void Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return;
    }
    IMG_Init(IMG_INIT_PNG);
    Game::window = SDL_CreateWindow(
            "Hunter Of Teens",
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

    // Initializing game data
    Game::c_gameState = PLAYING;
    player = new Player();
    player->init();
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
            
            if (e.key.repeat == 0) {
                if (e.key.keysym.sym == SDLK_s && !pMovement.up) {
                    pMovement.down = true;
                }
                else if (e.key.keysym.sym == SDLK_z) {
                    pMovement.up = true;
                }
                else if (e.key.keysym.sym == SDLK_q) {
                    pMovement.left = true;
                }
                else if (e.key.keysym.sym == SDLK_d && !pMovement.left) {
                    pMovement.right = true;
                }
            }
        }
        else if (e.type == SDL_KEYUP) {
            if (e.key.keysym.sym == SDLK_s) {
                pMovement.down = false;
            }
            else if (e.key.keysym.sym == SDLK_z) {
                pMovement.up = false;
            }
            else if (e.key.keysym.sym == SDLK_q) {
                pMovement.left = false;
            }
            else if (e.key.keysym.sym == SDLK_d) {
                pMovement.right = false;
            }
        }
    }
}

void Game::renderTextue(const char *filepath, SDL_Rect sRect, SDL_Rect dRect) {
    SDL_Surface *surface = IMG_Load(filepath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
    if (texture == NULL || surface == NULL) {
        perror("There is an error loading the SDL_Texture");
        return;
    }
    SDL_FreeSurface(surface);
    SDL_RenderCopy(Game::renderer, texture, &sRect, &dRect);
}


void Game::render() {
    switch (Game::c_gameState) {
        case MENU:
            break;
        case PLAYING:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            player->render(Game::renderer, player->rect);
            SDL_RenderPresent(renderer);
            break;
        case PAUSED:
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderClear(renderer);
                // buttons rect (TEST)
                SDL_Rect b_sRect = {0, 0, 32, 16};
                SDL_Rect b_dRect = {WIDTH/2, HEIGHT/2, 32*4, 16*4};
                Game::renderTextue("../res/button_atlas.png", b_sRect, b_dRect);
                SDL_RenderPresent(renderer);
                break;
            }
        case GAME_OVER:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            break;
    }
}

void Game::update() {
    player->rect = {player->x, player->y, 50, 50};
    if (pMovement.right) {
        player->move(1, 0);
    }
    else if (pMovement.left) {
        player->move(-1, 0);
    }
    else if (pMovement.down) {
        player->move(0, 1);
    }
    else if (pMovement.up) {
        player->move(0, -1);
    }
}

void Game::clean() {
    SDL_DestroyWindow(Game::window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}
