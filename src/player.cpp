#include "player.h"
#include "raylib.h"
#include <cstdio>
#include <iostream>

Player::Player(float StartPosX, float StartPosY){
  PosX = StartPosX;
  PosY = StartPosY;
  speed = 0.4f;
}


void Player::move(float dx, float dy) {
  PosX += dx;
  PosY += dy;

  // Need to re write this better
  if (PosX < 10){
    PosX = 10;
  }
  if (PosY < 10){
    PosY = 10;
  }
  if (PosY > 900-10){
    PosY = (900-10);
  }

if (PosX > 900-10){
    PosX = (900-10);
  }
}
void Player::Draw() { DrawCircle((int)PosX, (int)PosY, 10.0f, GRAY); }
