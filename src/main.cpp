#include "raylib.h"
#include <stdbool.h>
#include <iostream>

#define Window_Width_Px 800
#define Window_Height_Px 800

// Need to define some function here to use, predefined functions

void InitializeGame();
void ThecloseWindow();
void ProcessInput();
void DrawGame();
void ProcessUpdate();
bool isRunning();

class Player {
public:

  // Player Character Stats Variable
  float PosX, PosY;
  float speed;

  Player(float StartPosX, float StartPosY){
    PosX = StartPosX;
    PosY = StartPosY;
    speed = 5.0f;
 }

  void move(int dx, int dy){
    PosX+=dx;
    PosY+=dy;
  }
  void draw(){
    DrawCircle((int)PosX,(int)PosY,20,GRAY);
  }
    
};


Player human(100,100);

int main() {


  InitializeGame();
  while (isRunning()) {
    ProcessInput();
    ProcessUpdate();
    DrawGame();
  }

  ThecloseWindow();
  return 0;
}

void InitializeGame() {
  // Need to set the fps and also the window
  SetTargetFPS(60);
  InitWindow(Window_Width_Px, Window_Height_Px, "NotDecidedYet");
}

void ThecloseWindow() { CloseWindow(); }

void DrawGame() {
  BeginDrawing();
  human.draw();
  ClearBackground(WHITE);
  EndDrawing();
}

void ProcessInput() {

  if (IsKeyDown(KEY_W)){
    human.move(0,-human.speed);
  }
  if (IsKeyDown(KEY_S)){
    human.move(0,human.speed);
  }
  if (IsKeyDown(KEY_A)){
    human.move(-human.speed,0);
  }
  if (IsKeyDown(KEY_D)){
    human.move(human.speed,0);
  }
 
 
 
    
}
void ProcessUpdate() {}

bool isRunning() {
  return !WindowShouldClose(); // func will return true when the function to
                               // window close is triggered
}
