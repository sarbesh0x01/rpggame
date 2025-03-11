#include "include/player.h"
#include "SDL_rect.h"
#include "SDL_render.h"

Player::Player(int x, int y) {
  // Player initial Position
  Pos_X = 0;
  Pos_Y = 0;
}

void Player::move(int deltaX, int deltaY) {
  // pLayer movement
  Pos_Y += deltaY;
  Pos_X += deltaX;
}

void Player::render(SDL_Renderer *renderer) const {

  SDL_Rect playerRect = {Pos_X, Pos_Y, 50, 50};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &playerRect);
}

void Player::jump(int height) { Pos_Y += height; }

int Player::getPosX() const { return Pos_X; }

int Player::getPosY() const { return Pos_Y; }
