#ifndef VISUALS_HPP
#define VISUALS_HPP

#include <SDL2/SDL.h>
#include "../game/snake.hpp"

bool initSDL(SDL_Window *&window, SDL_Renderer *&renderer, int width, int height);
void handleInput(SnakeGame &game, int &delay, bool &bot);
void renderSnake(SDL_Renderer *renderer, const SnakeGame &game);
void renderSteps(SDL_Renderer* renderer, const SnakeGame &game);

#endif // VISUALS_HPP