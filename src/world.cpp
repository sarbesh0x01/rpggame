#include "include/world.h"
#include "../include/player.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <SDL_mouse.h>
#include <iostream>

World::World(int rows, int cols, int tileWidth, int tileHeight)
    : rows(rows), cols(cols), tileWidth(tileWidth), tileHeight(tileHeight) {
  offSetX = 600;
  offSetY = 200;
}

World::~World() {}

Point World::cartesianToIsometric(int x, int y) {
  Point iso;
  iso.x = (x - y) * (tileWidth / 2);
  iso.y = (x + y) * (tileHeight / 2);
  return iso;
}
Point World::screenToCartesion(int screenX, int screenY) {
  // First remove camera offset
  screenX -= offSetX;
  screenY -= offSetY;

  Point cart;
  cart.x = (screenX / (tileWidth / 2.0f) + screenY / (tileHeight / 2.0f)) / 2;
  cart.y = (screenY / (tileHeight / 2.0f) - screenX / (tileWidth / 2.0f)) / 2;
  return cart;
}
Point World::getTileScreenPosition(int x, int y) {
  Point iso = cartesianToIsometric(x, y);
  iso.x += offSetX;
  iso.y += offSetY;
  return iso;
}

bool World::isValidPosition(int x, int y) const {
  return x >= 0 && x < cols && y >= 0 && y < rows;
}

void World::centerCameraOnPlayer(const Player &player) {
  Point screenPos = getTileScreenPosition(player.getGridX(), player.getGridY());
  offSetX = (1080 / 2) - screenPos.x; // Assuming window width 1080
  offSetY = (800 / 2) - screenPos.y;  // Assuming window height 800
}

void World::fillDiamond(SDL_Renderer *renderer, int centerX, int centerY,
                        int width, int height) {

  SDL_Point points[5];

  points[0].x = centerX;
  points[0].y = centerY - height / 2; // Top

  points[1].x = centerX + width / 2;
  points[1].y = centerY; // Right

  points[2].x = centerX;
  points[2].y = centerY + height / 2; // Bottom

  points[3].x = centerX - width / 2;
  points[3].y = centerY; // Left

  points[4].x = points[0].x;
  points[4].y = points[0].y;
  SDL_RenderDrawLines(renderer, points, 5);
}
void World::render(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color

  // Loop through all tiles in the grid
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      // Get the screen position for this tile
      Point screenPos = getTileScreenPosition(x, y);
      // Draw the diamond tile
      fillDiamond(renderer, screenPos.x, screenPos.y, tileWidth, tileHeight);
      // You would typically check the tile type here and render different
      // graphics depending on what type of tile it is (grass, water, etc.)
    }
  }

  // Debug: Show which grid tile the mouse is over
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  Point mouseCart = screenToCartesion(mouseX, mouseY);
  int gridX = (int)mouseCart.x;
  int gridY = (int)mouseCart.y;

  if (isValidPosition(gridX, gridY)) {
    Point highlightPos = getTileScreenPosition(gridX, gridY);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 128); // Yellow highlight
    fillDiamond(renderer, highlightPos.x, highlightPos.y, tileWidth,
                tileHeight);

    // Draw coordinates as text if you have text rendering capabilities
    // Otherwise, just print to console
    std::cout << "Mouse over grid: (" << gridX << ", " << gridY << ")\n";
  }

  // Optional: Draw grid coordinates
  // This would require SDL_ttf for text rendering
  // If you want to add this feature later, you'll need to include SDL_ttf
  // and add code to render text at each tile position

  // Optional: Draw world axes for debugging
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // X-axis in red
  Point origin = getTileScreenPosition(0, 0);
  Point xAxis = getTileScreenPosition(cols - 1, 0);
  SDL_RenderDrawLine(renderer, origin.x, origin.y, xAxis.x, xAxis.y);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Y-axis in green
  Point yAxis = getTileScreenPosition(0, rows - 1);
  SDL_RenderDrawLine(renderer, origin.x, origin.y, yAxis.x, yAxis.y);
}

void World::getMousePos() {
  int printpos = SDL_GetMouseState(&mousepos_x, &mousepos_y);
}
