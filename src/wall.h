#ifndef WALL_H
#define WALL_H

#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include "SDL.h"

class Wall {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Wall(int grid_width, int grid_height, Direction direction, float speed)
    : grid_width(grid_width),
      grid_height(grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      x(static_cast<int>(random_w(engine))),
      y(static_cast<int>(random_h(engine))),
      direction(direction),
      speed(speed) {}

/*
  Wall(int grid_width, int grid_height, int length, bool vertical)
    : grid_width(grid_width),
      grid_height(grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      length(length),
      vertical(true) {}
*/

  void Update();
  
  Direction direction;
  float speed;
  float x;
  float y;

 private:

  int grid_width;
  int grid_height;
  bool _reverse{true};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void MoveCycle();
  void MoveBlock();

};

#endif
