
#include <cmath>
#include <iostream>
#include "snake.h"
#include "game.h"

void Snake::Update() {
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
}

void Snake::WallRedirect() {
  if (Game::_Wall == true) {
    switch (direction) {
      case Direction::kUp:
        head_y += speed;
        break;

      case Direction::kDown:
        head_y -= speed;
        break;

      case Direction::kLeft:
        head_x += speed;
        break;

      case Direction::kRight:
        head_x -= speed;
        break;
    }
  }
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}
