// InputHandler.cpp
#include <../include/InputHandler.h>
#include <iostream>

void InputHandler::handleButton(const SDL_MouseButtonEvent &event) {
  if (event.button == SDL_BUTTON_LEFT) {
    if (event.state == SDL_PRESSED) {
      std::cout << "Left button pressed at (" << event.x << ", " << event.y
                << ")\n";
    } else if (event.state == SDL_RELEASED) {
      std::cout << "Left button released at (" << event.x << ", " << event.y
                << ")\n";
    }
  }
}

void InputHandler::handleMotion(const SDL_MouseMotionEvent &event) {
  std::cout << "Mouse moved to (" << event.x << ", " << event.y << ")\n";
}
