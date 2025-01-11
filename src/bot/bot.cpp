#include "bot.hpp"
#include "../game/snake.hpp"
#include <queue>
#include <set>
#include <vector>
#include <iostream>

static const int dx[4] = {0, 0, -1, 1};
static const int dy[4] = {-1, 1, 0, 0};
static const Direction dir[4] = {UP, DOWN, LEFT, RIGHT};

bool isPathToTail(const SnakeGame &game, const std::pair<int, int> &head, const std::pair<int, int> &tail)
{
    if (head == tail)
        return true;

    int w = game.getWidth(), h = game.getHeight();
    std::vector<std::vector<bool>> visited(w, std::vector<bool>(h, false));
    std::queue<std::pair<int, int>> q;

    for (auto &s : game.getSnake())
        visited[s.first][s.second] = true;

    q.push(head);
    visited[head.first][head.second] = true;

    while (!q.empty())
    {
        auto [cx, cy] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (std::make_pair(nx, ny) == tail)
            {
                return true;
            }
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    return false;
}

Direction getDefaultDirection(const SnakeGame &game) {
    auto head = game.getHead();
    bool isLoop = false;
    Direction changeEmptyMove = RIGHT;
    Direction furthestFromTailMove = RIGHT;
    int furthestDistFromTail = -1;
    std::vector<Direction> possibleMoves;
    for (int i = 0; i < 4; i++) {
        int nx = head.first + dx[i], ny = head.second + dy[i];
        if (std::make_pair(nx, ny) == game.getTail()) {
            isLoop = true;
        }

        auto newGame = game;
        newGame.changeDirection(dir[i]);
        newGame.update(true);
        if (newGame.getHead() == std::make_pair(nx, ny) && !newGame.isGameOver() && isPathToTail(newGame, {nx, ny}, newGame.getTail())) {
            if (std::make_pair(nx, ny) != game.getTail())
                changeEmptyMove = dir[i];
            possibleMoves.push_back(dir[i]);
            int distFromTail = std::abs(nx - game.getTail().first) + std::abs(ny - game.getTail().second);
            if (distFromTail > furthestDistFromTail) {
                furthestDistFromTail = distFromTail;
                furthestFromTailMove = dir[i];
            }
        }
    }

    if (isLoop && possibleMoves.size() > 1)
        return changeEmptyMove;
    
    return furthestFromTailMove;
}

Direction getNextMove(const SnakeGame &game)
{
    int w = game.getWidth(), h = game.getHeight();
    std::vector<std::vector<bool>> visited(w, std::vector<bool>(h, false));
    std::vector<std::vector<Direction>> firstMove(w, std::vector<Direction>(h, RIGHT));
    std::vector<std::vector<SnakeGame>> firstGame(w, std::vector<SnakeGame>(h));

    std::queue<std::pair<int, int>> q;
    q.push(game.getHead());
    firstGame[game.getHead().first][game.getHead().second] = game;
    visited[game.getHead().first][game.getHead().second] = true;

    while (!q.empty())
    {
        auto [cx, cy] = q.front();
        q.pop();
        if (std::make_pair(cx, cy) == game.getFood())
        {
            // Found path
            Direction move = firstMove[cx][cy];
            return move;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (nx >= 0 && nx < w && ny >= 0 && ny < h && visited[nx][ny])
                continue;

            SnakeGame newGame = firstGame[cx][cy];
            newGame.changeDirection(dir[i]);
            newGame.update(true);
            if (newGame.getHead() == std::make_pair(nx, ny) && !newGame.isGameOver() && isPathToTail(newGame, {nx, ny}, newGame.getTail()))
            {
                visited[nx][ny] = true;
                firstMove[nx][ny] = (game.getHead().first == cx && game.getHead().second == cy) ? dir[i] : firstMove[cx][cy];
                firstGame[nx][ny] = newGame;
                q.push({nx, ny});
            }
        }
    }

    return getDefaultDirection(game);
}