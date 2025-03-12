#include "include/world.h"
#include "SDL_rect.h"
#include "SDL_render.h"

World::World(int rows, int cols, int tileWidth, int tileHeight)
    : rows(rows), cols(cols), tileWidth(tileWidth), tileHeight(tileHeight) {}

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

void World::render(SDL_Renderer *renderer) {
  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      Point iso = cartesionToIsometric(x, y);
      SDL_Rect tileRect = {iso.x, iso.y, tileWidth, tileHeight};
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderDrawRect(renderer, &tileRect);
    }
  }
}
