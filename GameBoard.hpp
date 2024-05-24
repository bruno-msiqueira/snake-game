#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <vector>
#include <set>
#include "Snake.hpp"
#include "Fruit.hpp"

class Snake;

class GameBoard {
public:
    enum class CellType {
        Empty,
        Border,
        Fruit,
        Snake,
        Obstacle
    };

    GameBoard(int width, int height, Snake* pSnake);

    void SetCell(std::pair<int, int> cell, CellType type);
    CellType GetCell(std::pair<int, int> cell) const;
    void AddObstacle(std::pair<int, int> cell);
    bool Update();
    std::pair<int, int> GetFruitPosition();

private:
    int m_gridWidth;
    int m_gridHeight;
    std::vector<std::vector<CellType>> m_grid;
    std::pair<int, int> m_lastSnakeSegmentPosition;
    std::pair<int, int> m_fruitPosition;
    Snake* m_pSnake;
    std::set<std::pair<int, int>> m_emptyPositions;

    std::pair<int, int> AddFruit();
};

#endif // GAMEBOARD_HPP