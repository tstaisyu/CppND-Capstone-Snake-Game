#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

//Source: https://wiki.libsdl.org/SDL2/SDL_SetWindowTitle
void Renderer::PauseMenu() {
  std::string menu{"Pause"};
  SDL_SetWindowTitle(sdl_window, menu.c_str());
}

void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &poison1, SDL_Point const &poison2, Wall const &block1, Wall const &block2, Wall const &block3, Wall const &block4, bool *bounus) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  if (*bounus) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xD7, 0x00, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0x66, 0xCD, 0xAA, 0xFF);
  }
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render poison1
  SDL_SetRenderDrawColor(sdl_renderer, 0x69, 0x4D, 0x9F, 0xFF);
  block.x = poison1.x * block.w;
  block.y = poison1.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render poison2
  SDL_SetRenderDrawColor(sdl_renderer, 0x69, 0x4D, 0x9F, 0xFF);
  block.x = poison2.x * block.w;
  block.y = poison2.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render wall
  SDL_SetRenderDrawColor(sdl_renderer, 0x55, 0x55, 0x55, 0xFF);
    block.x = block1.x * block.w;
    block.y = block1.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

  SDL_SetRenderDrawColor(sdl_renderer, 0x55, 0x55, 0x55, 0xFF);
    block.x = block2.x * block.w;
    block.y = block2.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);  

  SDL_SetRenderDrawColor(sdl_renderer, 0x55, 0x55, 0x55, 0xFF);
    block.x = block3.x * block.w;
    block.y = block3.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

  SDL_SetRenderDrawColor(sdl_renderer, 0x55, 0x55, 0x55, 0xFF);
    block.x = block4.x * block.w;
    block.y = block4.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);  
  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
