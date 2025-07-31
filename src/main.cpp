#include "main.h"
#include "raylib.h"
#include "player.h"


#define DefaultWindowHeight 900
#define DefaultWindowWidth 900

// Global Player
Player demoplayer(100,100);

bool isRunning() { return !WindowShouldClose(); }


void InitializeWindow() {
  InitWindow(DefaultWindowWidth, DefaultWindowHeight, "NotDecidedYet");
}

void DestroyWindow(){
  // WIll be simple right but later if nore things need to be cleanded up be
  CloseWindow();
}

void DrawGame(){
  BeginDrawing();
  ClearBackground(WHITE);
  demoplayer.Draw();
  EndDrawing();
}

void ProcessInput(){
  if (IsKeyDown(KEY_W)){
    demoplayer.move(0, -demoplayer.speed);
      }
  if (IsKeyDown(KEY_S)){
    demoplayer.move(0, demoplayer.speed);
      }
  if (IsKeyDown(KEY_A)){
    demoplayer.move(-demoplayer.speed, 0);
      }
  if (IsKeyDown(KEY_D)){
    demoplayer.move(demoplayer.speed, 0);
      }
}
  



