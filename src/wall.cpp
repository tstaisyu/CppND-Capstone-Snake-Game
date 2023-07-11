
#include <cmath>
#include <iostream>
#include "wall.h"
#include "game.h"

void Wall::Update() {
  SDL_Point prev_cell{
      static_cast<int>(x),
      static_cast<int>(y)};  // The head's cell before updating.
  Wall::MoveBlock();
  SDL_Point current_cell{
      static_cast<int>(x),
      static_cast<int>(y)};  // The block's cell after updating.
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
