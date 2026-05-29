#ifndef PLAYER_H_
#define PLAYER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct p_movement {
    bool down = false;
    bool up = false;
    bool left = false;
    bool right = false;
};

class Player {
    public:
        Player();
        ~Player();
        SDL_Rect rect;
        SDL_Texture *getTexture(SDL_Renderer *rend, const char* filename);
        void init();
        void render(SDL_Renderer *rend, SDL_Rect);
        void update();
        void jump();
        void move(int xFactor, int yFactor);
        int x, y;
        bool isDead;
        p_movement pMovement;
        double speed, velocity;
        SDL_Surface *psurface;
        SDL_Texture *ptexture;
};

#endif // !PLAYER_H_
