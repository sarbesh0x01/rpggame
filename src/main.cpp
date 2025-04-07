// main.cpp
#include "../include/Game.h"
#include <cstdio>

int main(int argc, char *argv[]) {
  Game game;
  if (!game.init()) {
    return 1;
  }
  game.run();
  return 0;
}
