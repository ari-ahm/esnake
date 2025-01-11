#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>
#include "../game/snake.hpp"
#include "../bot/bot.hpp"

TTF_Font* font;

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    window = SDL_CreateWindow("Snake SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * 20, height * 20, 0);
    if (!window) return false;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    if (TTF_WasInit() == 0 && TTF_Init() == -1) return false;
    font = TTF_OpenFont("Arial.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void handleInput(SnakeGame &game, int& delay, bool& bot) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        if (event.type == SDL_KEYDOWN) {
            if (!bot) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:    game.changeDirection(UP); break;
                    case SDLK_DOWN:  game.changeDirection(DOWN); break;
                    case SDLK_LEFT:  game.changeDirection(LEFT); break;
                    case SDLK_RIGHT: game.changeDirection(RIGHT); break;
                }
            }
            switch (event.key.keysym.sym) {
                case SDLK_c: delay = std::max(0, delay - 10); break;
                case SDLK_x: delay += 10; break;
                case SDLK_b: bot = !bot; break;
            }
        }
    }

    if (bot)
        game.changeDirection(getNextMove(game));
}

void renderSnake(SDL_Renderer *renderer, const SnakeGame &game) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw snake
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    auto snake = game.getSnake();
    for (int i = 0; i < (int)snake.size(); i++) {
        auto segment = snake[i];
        int d[4] = {2, 2, 2, 2};
        if (i > 0) {
            auto last = snake[i - 1];
            if (last.first == segment.first - 1) d[0] = 0;
            if (last.second == segment.second - 1) d[1] = 0;
            if (last.first == segment.first + 1) d[2] = 0;
            if (last.second == segment.second + 1) d[3] = 0;
        }
        if (i < (int)snake.size() - 1) {
            auto last = snake[i + 1];
            if (last.first == segment.first - 1) d[0] = 0;
            if (last.second == segment.second - 1) d[1] = 0;
            if (last.first == segment.first + 1) d[2] = 0;
            if (last.second == segment.second + 1) d[3] = 0;
        }
        

        SDL_Rect rect{segment.first * 20 + d[0], segment.second * 20 + d[1], 20 - d[0] - d[2], 20 - d[1] - d[3]};
        SDL_RenderFillRect(renderer, &rect);
    }

    // Draw food
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    auto food = game.getFood();
    SDL_Rect rect{food.first * 20, food.second * 20, 20, 20};
    SDL_RenderFillRect(renderer, &rect);
}

void renderSteps(SDL_Renderer* renderer, const SnakeGame &game)
{
    SDL_Color color = {255, 255, 255, 255};
    std::string scoreText = "Steps: " + std::to_string(game.getSteps());
    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
    if (!surface)
    {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect dstRect{10, 10, 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_DestroyTexture(texture);
}