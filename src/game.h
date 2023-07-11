#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "wall.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer *renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void BounusTime(bool *bounus); 
  void PauseToggle();
  void Pause();
  void Resume();

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point poison1;
  SDL_Point poison2;
  Wall block1;
  Wall block2;
  Wall block3;
  Wall block4;
//  Wall moving_wall;
  bool _pause{false};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  bool _bounus;

  int score{0};
  int best_score{0};

  void PlaceWall();
  void PlaceFood();
  void PlacePoison();
  void Update(Renderer *renderer);
  void DeathBlock();
  void GreatWallRedirect();
  };

#endif