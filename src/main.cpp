#include "SDL_video.h"
#include "include/core/Game.h"

//  Using heap here
// Game *game = nullptr;

int main(int argc, char *argv[]) {
  // This is using Heap with new
  // This is slower
  // Better use stack when we can
  // game = new Game;
  Game game;
  // Stack Uage
  // Better Use stack

  game.init("Elowen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
            0);

  while (game.running()) {
    game.handleEvent();
    game.update();
    game.render();
  }
  game.close();

  return 0;
}
