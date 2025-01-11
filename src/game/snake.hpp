#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

enum Direction { UP, DOWN, LEFT, RIGHT };

class SnakeGame {
public:
    SnakeGame();
    SnakeGame(int width, int height);
    SnakeGame(int width, int height, int seed);
    SnakeGame(const SnakeGame& other);
    SnakeGame& operator=(const SnakeGame& other);
    void reset();
    void changeDirection(Direction newDirection);
    void update(bool noFood = false);
    bool isGameOver() const;
    int getSteps() const;
    const std::vector<std::pair<int, int>>& getSnake() const;
    std::pair<int, int> getFood() const;
    int getWidth() const;
    int getHeight() const;
    std::pair<int, int> getHead() const;
    std::pair<int, int> getTail() const;
    bool checkCollision(int x, int y) const;

private:
    void generateFood();

    int width, height;
    int steps;
    bool gameOver;
    Direction direction;
    std::vector<std::pair<int, int>> snake;
    std::pair<int, int> food;
};

#endif // SNAKE_HPP