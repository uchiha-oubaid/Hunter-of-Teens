#ifndef GAME_H_
#define GAME_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define WIDTH 1280
#define HEIGHT 720

// the viewport
#define V_WIDTH 320
#define V_HEIGHT 640

enum GameState { MENU, PLAYING, PAUSED, GAME_OVER };

typedef struct {
    float x, y;
}Vector;

class Game {
    public:
        Game();
        ~Game();
        int running;
        int fullscreen;
        void init();
        void render();
        void update();
        void renderTextue(const char *filepath, SDL_Rect sRect, SDL_Rect dRect);
        void handleEvents(SDL_Event e);
        void clean();
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        GameState c_gameState;
};

#endif //GAME_H_
