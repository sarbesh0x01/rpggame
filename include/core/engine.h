// include/core/engine.h
#pragma once
#include <SDL.h>
#include <imgui.h>
#include <memory>

// Forward declarations
class InputManager;
class World;
class Player;
class GuiManager;

class Engine {
public:
  Engine();
  ~Engine();

  bool initialize();
  void run();
  void shutdown();

  SDL_Renderer *getRenderer() { return renderer; }
  SDL_Window *getWindow() { return window; }
  int getWindowWidth() const { return windowWidth; }
  int getWindowHeight() const { return windowHeight; }

private:
  // Window and rendering
  SDL_Window *window;
  SDL_Renderer *renderer;
  int windowWidth;
  int windowHeight;
  bool isRunning;

  // Subsystems
  std::unique_ptr<InputManager> inputManager;
  std::unique_ptr<World> world;
  std::unique_ptr<Player> player;
  std::unique_ptr<GuiManager> guiManager;

  void update();
  void render();
};
