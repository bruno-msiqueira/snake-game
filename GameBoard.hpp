#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <vector>
#include <set>
#include "Snake.hpp"

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

    GameBoard(unsigned int width, unsigned int height, unsigned int obstacleCount, Snake* pSnake);

    bool IsObstacle(std::pair<unsigned int, unsigned int> cell) const;
    void SetCell(std::pair<unsigned int, unsigned int> cell, CellType type);
    CellType GetCell(std::pair<unsigned int, unsigned int> cell) const;
    bool AddObstacles(unsigned int obstacleCount);
    bool Update();
    std::pair<unsigned int, unsigned int> GetFruitPosition();
    const std::set<std::pair<unsigned int, unsigned int>> &GetObstacles() const;
    unsigned int GetAvailableCells() const;

private:
    unsigned int m_gridWidth;
    unsigned int m_gridHeight;
    std::vector<std::vector<CellType>> m_grid;
    std::pair<unsigned int, unsigned int> m_fruitPosition;
    std::set<std::pair<unsigned int, unsigned int>> m_obstacles;
    Snake* m_pSnake;
    std::set<std::pair<unsigned int, unsigned int>> m_emptyPositions;
    unsigned int m_availableCells;

    void AddFruit();
};

#endif // GAMEBOARD_HPP