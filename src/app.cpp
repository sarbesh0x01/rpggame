#include "main.h"

int main() {

  InitializeWindow();
  while (isRunning()) {
    DrawGame();
    ProcessInput();
  }
  DestroyWindow();
}
