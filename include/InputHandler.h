
// InputHandler.h
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL_events.h>

class InputHandler {
public:
  static void handleButton(const SDL_MouseButtonEvent &event);
  static void handleMotion(const SDL_MouseMotionEvent &event);
};

#endif // INPUTHANDLER_H
