#include "include/world.h"
#include "SDL_rect.h"
#include "SDL_render.h"

World::World(int rows, int cols, int tileWidth, int tileHeight)
    : rows(rows), cols(cols), tileWidth(tileWidth), tileHeight(tileHeight) {
  offSetX = 400;
  offSetY = 200;
}

World::~World() {}

Point World::cartesionToIsometric(int x, int y) {
  Point iso;
  iso.x = (x - y) * (tileWidth / 2);
  iso.y = (x + y) * (tileHeight / 2);
  return iso;
}

Point World::isometricToCartesion(int x, int y) {
  Point cart;
  cart.x = (x / (tileWidth / 2) + y / (tileHeight / 2)) / 2;
  cart.y = (y / (tileHeight / 2) - x / (tileWidth / 2)) / 2;
  return cart;
}

Point World::getTileScreenPosition(int x, int y) {
  Point iso = cartesionToIsometric(x, y);
  iso.x += offSetX;
  iso.y += offSetY;
  return iso;
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
}
