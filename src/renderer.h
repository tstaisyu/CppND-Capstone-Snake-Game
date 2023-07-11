#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "wall.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void PauseMenu();
  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &poison1, SDL_Point const &poison2, Wall const &block1, Wall const &block2, Wall const &block3, Wall const &block4, bool *bounus);
  void UpdateWindowTitle(int score, int fps, int best_score);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif