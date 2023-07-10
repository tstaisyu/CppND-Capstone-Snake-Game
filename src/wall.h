#ifndef WALL_H
#define WALL_H

#include <vector>
#include "SDL.h"

class Wall {
 public:

  Wall(int length, bool vertical) {};

  void Update();

  void WallRedirect();
  bool SnakeCell(int x, int y);

  int size{4};
  float head_x;
  float head_y;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool vertical;
  int grid_width;
  int grid_height;
};

#endif
