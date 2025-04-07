#pragma once

#include "./player.h"
#include "SDL_render.h"
#include <string>
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

  void getMousePos();

  void loadTileTexture(SDL_Renderer *renderer, const std::string &path);

private:
  int rows;
  int cols;
  int tileWidth;
  int tileHeight;

  int mousepos_x;
  int mousepos_y;

  int offSetX;
  int offSetY;

  SDL_Texture *tileTexture; // Single tile or tileset
  void fillDiamond(SDL_Renderer *renderer, int centerX, int centerY, int width,
                   int height);
};
