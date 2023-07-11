(This repository is cloned from https://github.com/udacity/CppND-Capstone-Snake-Game)

# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

In this project, I added several functions to the Snake Game starter code based on what I learned in the Udacity C++ Nanodegree Program.

## Additional Features
* Bounus food (yellow): Randomly normal food (greed) changes.
* 4 death block: Move each direction and reverse the direction random-cyclically. Touching them will kill the snake.
* Walls around the edges of the display where the direction of the snake reverses if going out.
* Two purple poisons which make score 0 and cause loss of the body.
* Pause function: Press "SPACE" key.
* Best score: On top of the display.

## Rubric Points

1. The project demonstrates an understanding of C++ functions and control structures.
* game.cpp, line 190 - Add a direction reveral funciton.

2. The project accepts user input and processes the input.
* controller.cpp, line 41 - Add a pause function with using "Space" key. 

3. The project uses Object Oriented Programming techniques.
* wall.h / wall.cpp - Create "Wall" class in new separate files.

4. Class constructors utilize member initialization lists.
* In "Wall" class, use member initialization lists with direction and speed as arguments.

5 The project uses multithreading.
* wall.cpp, line 11, 19 - The death blocks reversal.
* game.cpp, line 81, 163 - Bounus food time.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
