#include "main.h"

int main() {
  // This is the main function for the code to run
 
  Game game;
  bool sucess;

  sucess = game.Initialize();
  if (sucess) {
    game.RunLoop();
  }
  game.CloseGame();
}
