#include "game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "SDL.h"
#include "snake.h"
#include "wall.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      block1(grid_width, grid_height, Wall::Direction::kRight, 0.06),
      block2(grid_width, grid_height, Wall::Direction::kUp, 0.08),    
      block3(grid_width, grid_height, Wall::Direction::kLeft, 0.09),
      block4(grid_width, grid_height, Wall::Direction::kDown, 0.07),    
    //  moving_wall(grid_width, grid_height, 4, true),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceWall();
  PlaceFood();
  PlacePoison();
}

void Game::Run(Controller const &controller, Renderer *renderer,
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
    controller.HandleInput(running, snake, *this);
    GreatWallRedirect();
    DeathBlock();
    Update(renderer);
    renderer->Render(snake, food, poison1, poison2, block1, block2, block3, block4, &_bounus);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer->UpdateWindowTitle(score, frame_count, best_score);
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

void Game::BounusTime(bool *bounus) {
  std::this_thread::sleep_for(std::chrono::milliseconds(7000));
  *bounus = false;
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
  int x1, y1, x2, y2, x3, y3, x4, y4;
  while (true) {
    x1 = random_w(engine);
    y1 = random_h(engine);
    x2 = random_w(engine);
    y2 = random_h(engine);    
    x3 = random_w(engine);
    y3 = random_h(engine);
    x4 = random_w(engine);
    y4 = random_h(engine);    
    // Check that the location is not occupied by a snake item before placing
    // food.
      if (!snake.SnakeCell(x1, y1) && !snake.SnakeCell(x2, y2) && !snake.SnakeCell(x3, y3) && !snake.SnakeCell(x4, y4)) {
        block1.x = x1;
        block1.y = y1;
        block2.x = x2;
        block2.y = y2;
        block3.x = x3;
        block3.y = y3;
        block4.x = x4;
        block4.y = y4;
        return;
      }
  }
}

void Game::Update(Renderer *renderer) {
  if (this->_pause) {
    renderer->PauseMenu();   
    return;
  }
  if (!snake.alive) return;

  snake.Update();
  block1.Update();
  block2.Update();
  block3.Update();
  block4.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);


  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    if (_bounus) {
      score += 5;
    } else {
      score++;
    }
    if (best_score < score) {
      best_score = score;
    }
    PlaceFood();
    PlacePoison();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
    if(score % 4 == 0) {
      _bounus = true;
      std::thread BounusThread(&Game::BounusTime, this, &_bounus);
      BounusThread.detach();
    }
  }
  
    // Check if there are poisons over here
  if (poison1.x == new_x && poison1.y == new_y || poison2.x == new_x && poison2.y == new_y) {
    score = 0;
    PlacePoison();
    PlaceFood();
    // Grow snake and increase speed.
    snake.LostBody();
    snake.speed = 0.2;
  }
}

// the direction of snake reverses when the snake hits the blocks. 
void Game::DeathBlock() {

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
    if (int(block1.x) == new_x && int(block1.y) == new_y || int(block2.x) == new_x && int(block2.y) == new_y || int(block3.x) == new_x && int(block3.y) == new_y || int(block4.x) == new_x && int(block4.y) == new_y ) {
      snake.alive = false;
    }
}

// the direction of snake reverses when the snake arrive at the edges of the screen. 
void Game::GreatWallRedirect() {

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
    if (new_x < 1 || new_y < 1 || new_x > 30 || new_y > 30 ) {
      snake.Redirect();
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }


void Game::PauseToggle() {
  if (this->_pause == false) {
    Pause();
  } else {
    Resume();
  }
}

void Game::Pause() {this->_pause = true;}

void Game::Resume() {this->_pause = false;}
