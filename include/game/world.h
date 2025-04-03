// include/game/world.h
#pragma once
#include <SDL.h>
#include <vector>

struct Point {
  int x;
  int y;
};

// Forward declaration
class Player;

class World {
public:
  World(int rows, int cols, int tileWidth, int tileHeight);
  ~World();

  void render(SDL_Renderer *renderer);
  Point getTileScreenPosition(int x, int y);
  bool isValidPosition(int x, int y) const;
  void centerCameraOnPlayer(const Player &player);
  Point screenToCartesion(int screenX, int screenY);

  int getOffsetX() const { return offSetX; }
  int getOffsetY() const { return offSetY; }

private:
  int rows;
  int cols;
  int tileWidth;
  int tileHeight;
  int offSetX;
  int offSetY;
  int mousepos_x;
  int mousepos_y;

  Point cartesianToIsometric(int x, int y);
  void fillDiamond(SDL_Renderer *renderer, int centerX, int centerY, int width,
                   int height);
};
