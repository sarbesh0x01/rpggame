// src/game/player.cpp
#include "../../include/game/player.h"
#include "../../include/game/world.h"

Player::Player(int startX, int startY, World &w)
    : gridX(startX), gridY(startY), world(w) {}

void Player::move(int deltaX, int deltaY) {
  // Move in grid space first
  int newX = gridX + deltaX;
  int newY = gridY + deltaY;

  // Add collision checking here if needed
  if (world.isValidPosition(newX, newY)) {
    gridX = newX;
    gridY = newY;
  }
}

void Player::render(SDL_Renderer *renderer) {
  Point screenPos = world.getTileScreenPosition(gridX, gridY);
  SDL_Rect playerRect = {
      screenPos.x - 25, // Center horizontally (player width 50)
      screenPos.y - 50, // Align with tile top (player height 50)
      50, 50};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &playerRect);
}

void Player::jump(int height) { Pos_Y += height; }

void Player::handleEvent(const SDL_Event &e) {
  if (e.type == SDL_KEYDOWN) {
    switch (e.key.keysym.sym) {
    case SDLK_w:
    case SDLK_UP:
      move(0, -1);
      break;

    case SDLK_s:
    case SDLK_DOWN:
      move(0, 1);
      break;

    case SDLK_a:
    case SDLK_LEFT:
      move(-1, 0);
      break;

    case SDLK_d:
    case SDLK_RIGHT:
      move(1, 0);
      break;
    }
  }
}
