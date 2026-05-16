#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include "game.hpp"

int main() {
    Game *game = new Game();
    SDL_Event e;
    game->init();

    // for frame cap
    int frameDelay = 16;
    Uint32 frameStart;
    int frameTime;
    while (game->running) {
        frameStart = SDL_GetTicks();
        game->handleEvents(e);
        game->update();
        game->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime > frameDelay) {
            SDL_Delay(frameTime);
        }
    }
    game->clean();
    return 0;
}
