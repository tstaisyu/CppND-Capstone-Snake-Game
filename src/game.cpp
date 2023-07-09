#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceWall();
  PlaceFood();
  PlacePoison();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, poison1, poison2, wall1, wall2, wall3, wall4);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::PlacePoison() {
  int x1, y1, x2, y2;
  while (true) {
    x1 = random_w(engine);
    y1 = random_h(engine);
    x2 = random_w(engine);
    y2 = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x1, y1) && !snake.SnakeCell(x2, y2)) {
      poison1.x = x1;
      poison1.y = y1;
      poison2.x = x2;
      poison2.y = y2;
      return;
    }
  }
}

void Game::PlaceWall() {
  int x, y1, y2, y3, y4;
  while (true) {
    x = random_w(engine);
    y1 = 0;
    y2 = 0 + 1;
    y3 = 0 + 2;
    y4 = 0 + 3;
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y1) && !snake.SnakeCell(x, y2) && !snake.SnakeCell(x, y3) && !snake.SnakeCell(x, y4)) {
      wall1.x = x;
      wall1.y = y1;
      wall2.x = x;
      wall2.y = y2;
      wall3.x = x;
      wall3.y = y3;
      wall4.x = x;
      wall4.y = y4;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  
    // Check if there are poisons over here
  if (poison1.x == new_x && poison1.y == new_y || poison2.x == new_x && poison2.y == new_y) {
    score = 0;
    PlacePoison();
    // Grow snake and increase speed.
    snake.LostBody();
    snake.speed = 0.1;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }