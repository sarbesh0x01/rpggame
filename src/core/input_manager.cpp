// src/core/input_manager.cpp
#include "../../include/core/input_manager.h"

InputManager::InputManager() : keyboardState(nullptr) {
  keyboardState = SDL_GetKeyboardState(nullptr);
  mouseX = 0;
  mouseY = 0;
  mouseButtons = 0;
}

InputManager::~InputManager() {}

bool InputManager::processInput() {
  // Update mouse state
  mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);

  // Process events
  while (SDL_PollEvent(&event)) {
    // Check for quit event first
    if (event.type == SDL_QUIT) {
      return false;
    }

    // Handle specific events with callbacks
    if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
      if (mouseButtonCallback) {
        mouseButtonCallback(event.button);
      }
    } else if (event.type == SDL_MOUSEMOTION) {
      if (mouseMotionCallback) {
        mouseMotionCallback(event.motion);
      }
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      if (keyCallback) {
        keyCallback(event);
      }
    }
  }

  // Update keyboard state
  keyboardState = SDL_GetKeyboardState(nullptr);

  return true;
}

bool InputManager::isKeyPressed(SDL_Scancode key) const {
  return keyboardState[key] != 0;
}

void InputManager::getMousePosition(int &x, int &y) const {
  x = mouseX;
  y = mouseY;
}

void InputManager::registerMouseButtonCallback(
    std::function<void(SDL_MouseButtonEvent &)> callback) {
  mouseButtonCallback = callback;
}

void InputManager::registerMouseMotionCallback(
    std::function<void(SDL_MouseMotionEvent &)> callback) {
  mouseMotionCallback = callback;
}

void InputManager::registerKeyCallback(
    std::function<void(const SDL_Event &)> callback) {
  keyCallback = callback;
}
