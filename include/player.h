#pragma once

#include "./world.h"
#include "SDL_events.h"
#include <SDL.h>

class World;

class Player {

public:
  Player(int startX, int startY, World &w);

  void move(int deltaX, int deltaY);

  void jump(int height);
  void render(SDL_Renderer *renderer);
  void handelEvent(const SDL_Event &e);

  int getPosX() const;
  int getPosY() const;

  int getGridX() const { return gridX; }
  int getGridY() const { return gridY; }

private:
  int gridX, gridY; // Grid position (cartesian coordinates)
  World &world;     // Reference to your World object
  int Pos_X;
  int Pos_Y;
};
