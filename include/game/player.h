// include/game/player.h
#pragma once
#include <SDL.h>

// Forward declaration
class World;

class Player {
public:
  Player(int startX, int startY, World &world);

  void render(SDL_Renderer *renderer);
  void handleEvent(const SDL_Event &e);
  void move(int deltaX, int deltaY);
  void jump(int height);

  int getGridX() const { return gridX; }
  int getGridY() const { return gridY; }
  int getPosX() const { return Pos_X; }
  int getPosY() const { return Pos_Y; }

private:
  int gridX;
  int gridY;
  int Pos_X = 0;
  int Pos_Y = 0;
  World &world;
};
