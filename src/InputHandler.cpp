#include "../include/InputHandler.h"
#include "../include/player.h"
#include "../include/world.h"
#include <algorithm> // For std::max and std::min
#include <iostream>

InputHandler::InputHandler(Player &playerRef, World &worldRef)
    : player(playerRef), world(worldRef) {}

void InputHandler::handleButton(const SDL_MouseButtonEvent &event) {
  if (event.button == SDL_BUTTON_LEFT && event.state == SDL_PRESSED) {
    // Get raw screen coordinates
    int sx = event.x;
    int sy = event.y;

    // Convert screen coordinates to cartesian (grid) coordinates using World's
    // method
    Point cartesian = world.screenToCartesion(sx, sy);
    int wx = cartesian.x;
    int wy = cartesian.y;

    // Check if this is a valid position in the world
    if (world.isValidPosition(wx, wy)) {
      std::cout << "Mouse clicked at screen (" << sx << ", " << sy
                << ") → Moving player to isometric grid (" << wx << ", " << wy
                << ")\n";

      // Move player to the correct tile
      player.setPosition(wx, wy);
    }
  }
}

void InputHandler::handleMotion(const SDL_MouseMotionEvent &event) {}
void InputHandler::ChangeMouseScreenToIsometric() {}
