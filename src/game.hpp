#ifndef GAME_H_
#define GAME_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define WIDTH 800
#define HEIGHT 700

class Game {
    public:
        Game();
        ~Game();
        int running;
        int fullscreen;
        void init();
        void render();
        void update();
        void handleEvents(SDL_Event e);
        void clean();
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif //GAME_H_
