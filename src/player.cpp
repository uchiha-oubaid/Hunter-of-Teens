#include "player.hpp"
//#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

Player::Player() {}
Player::~Player() {}

void Player::init() {
    Player::x = 50;
    Player::y = 50;
    Player::speed = 10;
}

SDL_Texture *Player::getTexture(SDL_Renderer *rend, const char *filename) {
    SDL_Surface *textSurface = IMG_Load(filename);
    SDL_Texture *text = SDL_CreateTextureFromSurface(rend, textSurface);
    return text;
}

void Player::render(SDL_Renderer *rend, SDL_Rect rect) {
    SDL_RenderFillRect(rend, &rect);
}

void Player::update() {}
void Player::jump() {}
void Player::move(int xFactor, int yFactor) {
    Player::x += xFactor * Player::speed;
    Player::y += yFactor * Player::speed;
}
