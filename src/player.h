#define once

class Player {
 public:
  float PosX, PosY;
  float speed;
  float PosXMax, PosYMax;
  float xMax, yMax;

  Player(float StartPosX, float StartPosY);
  void move(float dx, float dy);
  void Draw();
};
