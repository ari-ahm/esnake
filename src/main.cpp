#include "visuals/visuals.hpp"
#include "bot/bot.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    int width = 20;
    int height = 20;
    unsigned int seed = static_cast<unsigned int>(time(nullptr)); // Default seed is current time

    if (argc > 1)
        width = std::stoi(argv[1]);
    if (argc > 2)
        height = std::stoi(argv[2]);
    if (argc > 3)
        seed = std::stoul(argv[3]);

    SnakeGame game(width, height, seed);
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (!initSDL(window, renderer, game.getWidth(), game.getHeight()))
        return -1;

    int delay = 100; // Initial delay in milliseconds
    bool bot = true;
    while (!game.isGameOver())
    {
        handleInput(game, delay, bot);
        renderSnake(renderer, game);
        renderSteps(renderer, game);
        SDL_RenderPresent(renderer);
        game.update();
        SDL_Delay(delay);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}