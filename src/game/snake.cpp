#include "snake.hpp"
#include <iostream>

SnakeGame::SnakeGame(int width, int height, int seed)
    : width(width), height(height), steps(0), gameOver(false), direction(RIGHT) {
    std::cerr << "Seed: " << seed << std::endl;
    std::srand(seed);
    reset();
}

SnakeGame::SnakeGame(int width, int height)
    : SnakeGame(width, height, time(nullptr)) {}

SnakeGame::SnakeGame() {}

void SnakeGame::reset() {
    snake.clear();
    snake.push_back({width / 2, height / 2});
    steps = 0;
    gameOver = false;
    direction = RIGHT;
    generateFood();
}

void SnakeGame::changeDirection(Direction newDirection) {
    if ((direction == UP && newDirection != DOWN) ||
        (direction == DOWN && newDirection != UP) ||
        (direction == LEFT && newDirection != RIGHT) ||
        (direction == RIGHT && newDirection != LEFT) ||
        snake.size() <= 2) {
        direction = newDirection;
    }
}

void SnakeGame::update(bool noFood) {
    if (gameOver) return;

    steps++;

    std::pair<int, int> head = snake.front();
    switch (direction) {
        case UP: head.second--; break;
        case DOWN: head.second++; break;
        case LEFT: head.first--; break;
        case RIGHT: head.first++; break;
    }

    if (head != food) {
        snake.pop_back();
    }

    if (head.first < 0 || head.first >= width || head.second < 0 || head.second >= height || checkCollision(head.first, head.second)) {
        gameOver = true;
        return;
    }

    snake.insert(snake.begin(), head);

    if (head == food && !noFood)
        generateFood();
}

bool SnakeGame::isGameOver() const {
    return gameOver;
}

int SnakeGame::getSteps() const {
    return steps;
}

const std::vector<std::pair<int, int>>& SnakeGame::getSnake() const {
    return snake;
}

std::pair<int, int> SnakeGame::getFood() const {
    return food;
}

void SnakeGame::generateFood() {
    std::vector<std::pair<int, int>> freeCells;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (!checkCollision(x, y)) {
                freeCells.push_back({x, y});
            }
        }
    }

    if (!freeCells.empty()) {
        int index = std::rand() % freeCells.size();
        food = freeCells[index];
    } else {
        gameOver = true; // No free cells left, game over
        std::cout << "You Won!!!! steps taken : " << steps << "\n";
    }
}

bool SnakeGame::checkCollision(int x, int y) const {
    for (const auto& segment : snake) {
        if (segment.first == x && segment.second == y) {
            return true;
        }
    }
    return false;
}

int SnakeGame::getWidth() const {
    return width;
}

int SnakeGame::getHeight() const {
    return height;
}

SnakeGame::SnakeGame(const SnakeGame &other)
    : width(other.width), height(other.height), steps(other.steps), gameOver(other.gameOver), direction(other.direction), snake(other.snake), food(other.food) {}

SnakeGame &SnakeGame::operator=(const SnakeGame &other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        steps = other.steps;
        gameOver = other.gameOver;
        direction = other.direction;
        snake = other.snake;
        food = other.food;
    }
    return *this;
}

std::pair<int, int> SnakeGame::getHead() const {
    return snake.front();
}

std::pair<int, int> SnakeGame::getTail() const {
    return snake.back();
}