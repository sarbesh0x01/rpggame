#pragma once

#include "./player.h"
#include "SDL_render.h"
struct Point {
  int x;
  int y;
};

class Player;

class World {

public:
  World(int rows, int cols, int tileWidth, int tileHeight);
  ~World();

  Point cartesianToIsometric(int x, int y);
  Point screenToCartesion(int x, int y);

  bool isValidPosition(int x, int y) const;

  void render(SDL_Renderer *renderer);

  Point getTileScreenPosition(int x, int y);

  void centerCameraOnPlayer(const Player &player);

  void CreateIsometricTiles();

  int getTileWidth() const;
  int getTileHeight() const;

private:
  int rows;
  int cols;
  int tileWidth;
  int tileHeight;

  int offSetX;
  int offSetY;

  void fillDiamond(SDL_Renderer *renderer, int centerX, int centerY, int width,
                   int height);
};
