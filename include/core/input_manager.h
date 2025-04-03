// include/core/input_manager.h
#pragma once
#include <SDL.h>
#include <functional>
#include <unordered_map>

class InputManager {
public:
  InputManager();
  ~InputManager();

  bool processInput();
  bool isKeyPressed(SDL_Scancode key) const;
  void getMousePosition(int &x, int &y) const;

  void registerMouseButtonCallback(
      std::function<void(SDL_MouseButtonEvent &)> callback);
  void registerMouseMotionCallback(
      std::function<void(SDL_MouseMotionEvent &)> callback);
  void registerKeyCallback(std::function<void(const SDL_Event &)> callback);

private:
  SDL_Event event;
  const Uint8 *keyboardState;
  int mouseX, mouseY;
  Uint32 mouseButtons;

  std::function<void(SDL_MouseButtonEvent &)> mouseButtonCallback;
  std::function<void(SDL_MouseMotionEvent &)> mouseMotionCallback;
  std::function<void(const SDL_Event &)> keyCallback;
};
