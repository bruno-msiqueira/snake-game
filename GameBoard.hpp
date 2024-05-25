#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <vector>
#include <set>
#include "Snake.hpp"

class Snake;

class GameBoard {
public:
    // The CellType enum represents the type of a cell on the game board.
    enum class CellType {
        Unknown,
        Empty,
        Border,
        Fruit,
        Snake,
        Obstacle
    };

    // Constructor initializes the game board.
    GameBoard(unsigned int width, unsigned int height, unsigned int obstacleCount, Snake* pSnake);

    // Update updates the game board state.
    void Update(bool fruitEaten);

    // SetCell sets the cell at the given position to the given type.
    void SetCell(std::pair<unsigned int, unsigned int> cell, CellType type);

    // GetCell returns the type of the cell at the given position.
    CellType GetCell(std::pair<unsigned int, unsigned int> cell) const;

    // GetAvailableCells returns the number of available cells on the game board.
    unsigned int GetAvailableCells() const;

    // IsObstacle checks if the cell at the given position is an obstacle.
    bool IsObstacle(std::pair<unsigned int, unsigned int> cell) const;

    // GetObstacles returns the set of obstacle positions.
    const std::set<std::pair<unsigned int, unsigned int>> &GetObstacles() const;

    // GetFruitPosition returns the position of the fruit.
    std::pair<unsigned int, unsigned int> GetFruitPosition() const;

private:
    unsigned int m_gridWidth;
    unsigned int m_gridHeight;
    std::vector<std::vector<CellType>> m_grid;
    std::pair<unsigned int, unsigned int> m_fruitPosition;
    std::set<std::pair<unsigned int, unsigned int>> m_obstacles;
    Snake* m_pSnake;
    std::set<std::pair<unsigned int, unsigned int>> m_emptyPositions;
    unsigned int m_availableCells;

    // AddObstacles adds obstacles to the game board.
    bool AddObstacles(unsigned int obstacleCount);

    // AddFruit adds a fruit to the game board.
    void AddFruit();
};

#endif // GAMEBOARD_HPP