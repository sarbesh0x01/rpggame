#pragma once
#include "raylib.h"
// Game loop and everything should connect to main as possinble

enum GameState { GAME_PAUSE, GAME_RUNNING, GAME_QUIT };

class Game {
 public:

    Camera camera = { 0 };

  Game();
  bool Initialize();
  void RunLoop();
  void ProcessInput();
  void UpdateGame();
  void CloseGame();
  void DrawGame();
 private:
  bool mRunning;
};

