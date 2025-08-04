#include "main.h"

int main() {
  // This is the main function for the code to run

  Game game;
  bool sucess;
  // things working
  sucess = game.Initialize();
  if (sucess) {
    game.RunLoop();
  }
  game.CloseGame();
}
