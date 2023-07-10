#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "wall.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  bool _Wall{false};
  
 private:
  Snake snake;
  SDL_Point food;
  SDL_Point poison1;
  SDL_Point poison2;
  Wall wall1, wall2, wall3, wall4;
  std::vector<std::vector<SDL_Point>> wall_list;


  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceWall();
  void WallCheck(int x, int y);
  void PlaceFood();
  void PlacePoison();
  void Update();
};

#endif