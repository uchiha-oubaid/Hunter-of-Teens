#ifndef PLAYER_H_
#define PLAYER_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Player {
    public:
        Player();
        ~Player();
        SDL_Texture getTexture(std::string filename);
        void render(int x, int y);
        void update(double speed);
        void jump(double velocity);
    private:
        bool isDead;
        SDL_Surface *psurface;
        SDL_Texture *ptexture;
};

#endif // !PLAYER_H_
