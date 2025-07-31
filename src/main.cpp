#include "main.h"
#include "raylib.h"


#define DefaultWindowHeight 900
#define DefaultWindowWidth 800

bool isRunning() { return !WindowShouldClose(); }


void InitializeWindow() {
  InitWindow(DefaultWindowWidth, DefaultWindowHeight, "NotDecidedYet");
}


