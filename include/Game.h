#ifndef GAME_H
#define GAME_H

#include "../include/InputHandler.h" // Include the header for InputHandler
#include "../include/player.h"
#include <SDL.h>

class Player;
class World;

class Game {
public:
  Game();
  ~Game();
  bool init();
  void run();
  void cleanup();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning;

  // Add your world, player, and other game objects as members
  World world;
  Player player;
  InputHandler inputHandler; // Declare the InputHandler instance
};

#endif // GAME_H

