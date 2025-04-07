#include "include/player.h"
#include "../include/world.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "imgui_impl_sdl2.h"
#include <imgui.h>
#include <iostream>

Player::Player(int startX, int startY, World &w)
    : gridX(startX), gridY(startY), world(w) {}

void Player::move(int deltaX, int deltaY) {
  int newX = gridX + deltaX;
  int newY = gridY + deltaY;

  // Check for collision before moving
  if (world.isValidPosition(newX, newY)) {
    setPosition(
        newX,
        newY); // Use setPosition to update both grid and screen coordinates
  }
}

void Player::render(SDL_Renderer *renderer) {
  // Draw player at the correct screen position
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for player

  // Draw a filled diamond at the player's position
  const int playerSize = 24; // Slightly smaller than a tile

  // Draw diamond shape
  SDL_Point points[5];
  points[0].x = screenX;
  points[0].y = screenY - playerSize / 2; // Top
  points[1].x = screenX + playerSize / 2;
  points[1].y = screenY; // Right
  points[2].x = screenX;
  points[2].y = screenY + playerSize / 2; // Bottom
  points[3].x = screenX - playerSize / 2;
  points[3].y = screenY; // Left
  points[4].x = points[0].x;
  points[4].y = points[0].y; // Back to top

  // Fill the player diamond
  for (int i = 0; i < 4; i++) {
    SDL_RenderDrawLine(renderer, screenX, screenY, points[i].x, points[i].y);
  }
  SDL_RenderDrawLines(renderer, points, 5);

  // Draw a small cross at the center for debugging
}

void Player::jump(int height) { Pos_Y += height; }

int Player::getPosX() const { return Pos_X; }

int Player::getPosY() const { return Pos_Y; }

void Player::handelEvent(const SDL_Event &e) {

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

void Player::setPosition(int wx, int wy) {
  // Set grid position
  gridX = wx;
  gridY = wy;

  // Get screen position from the world
  Point screenPos = world.getTileScreenPosition(gridX, gridY);
  screenX = screenPos.x;
  screenY = screenPos.y;

  std::cout << "Player moved to grid (" << gridX << ", " << gridY
            << ") with screen position (" << screenX << ", " << screenY
            << ")\n";
}
