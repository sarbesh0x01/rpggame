#pragma once

#include "SDL_events.h"
#include <SDL.h>

class Player {

public:
  Player(int x = 0, int y = 0);

  void move(int deltaX, int deltaY);

  void jump(int height);
  void render(SDL_Renderer *renderer) const;
  void handelEvent(const SDL_Event &e);

  int getPosX() const;
  int getPosY() const;

private:
  int Pos_X;
  int Pos_Y;
};
