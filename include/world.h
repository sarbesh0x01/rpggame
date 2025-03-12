#pragma once

#include "SDL_render.h"
struct Point {
  int x;
  int y;
};

class World {

public:
  World(int rows, int cols, int tileWidth, int tileHeight);
  ~World();

  Point cartesionToIsometric(int x, int y);
  Point isometricToCartesion(int x, int y);

  void render(SDL_Renderer *renderer);

private:
  int rows;
  int cols;
  int tileWidth;
  int tileHeight;
};
