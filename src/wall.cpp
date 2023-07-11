
#include <cmath>
#include <iostream>
#include "wall.h"
#include "game.h"

void Wall::Update() {
  SDL_Point prev_cell{
      static_cast<int>(x),
      static_cast<int>(y)};  // The head's cell before updating.
  std::thread MoveThread(&Wall::MoveCycle, this);
  MoveThread.detach();
  Wall::MoveBlock();
  SDL_Point current_cell{
      static_cast<int>(x),
      static_cast<int>(y)};  // The block's cell after updating.
}

void Wall::MoveCycle() {
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> distr(2000, 4000);
  int cycleDuration = distr(engine);
  auto now = std::chrono::system_clock::now();
  _reverse = true;
  while (_reverse) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto end = std::chrono::system_clock::now();
    auto lambda = std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count();
    if (lambda > cycleDuration) {
      switch (direction) {
      case Direction::kUp:
        direction = Direction::kDown;
        now = std::chrono::system_clock::now();
        cycleDuration = distr(engine);
        _reverse = false;
        break;

      case Direction::kDown:
        direction = Direction::kUp;
        now = std::chrono::system_clock::now();
        cycleDuration = distr(engine);
        _reverse = false;
        break;

      case Direction::kLeft:
        direction = Direction::kRight;
        now = std::chrono::system_clock::now();
        cycleDuration = distr(engine);
        _reverse = false;
        break;

      case Direction::kRight:
        direction = Direction::kLeft;
        now = std::chrono::system_clock::now();
        cycleDuration = distr(engine);
        _reverse = false;
        break;      
      }
    }
  }
}

void Wall::MoveBlock() {
  switch (direction) {
    case Direction::kUp:
      y -= speed;
      break;

    case Direction::kDown:
      y += speed;
      break;

    case Direction::kLeft:
      x -= speed;
      break;

    case Direction::kRight:
      x += speed;
      break;
  }

  x = fmod(x + grid_width, grid_width);
  y = fmod(y + grid_height, grid_height);
}
/*
Wall::Wall(int grid_width, int grid_height, int length, bool vertical) {
  x(static_cast<int>(random_w(engine))),
  y(static_cast<int>(random_h(engine)))
}
*/
