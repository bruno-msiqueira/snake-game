#include <iostream>
#include <conio.h>

#include "GameBoard.hpp"

GameBoard::GameBoard(unsigned int width, unsigned int height,
                     unsigned int obstacleCount, Snake* pSnake)
    :   m_gridWidth(width),
        m_gridHeight(height),
        m_pSnake(pSnake),
        m_grid(height,
               std::vector<CellType>(width, CellType::Empty))
{
    srand(time(0)); // Initialize random seed

    // Initialize the grid and the set of empty positions
    for (int x = 0; x < m_gridWidth; ++x) {
        for (int y = 0; y < m_gridHeight; ++y) {
            std::pair<unsigned int, unsigned int> cell = std::make_pair(x, y);

            // If the cell is on the border
            if (x == 0 || y == 0 || x == m_gridWidth - 1 || y == m_gridHeight - 1) {
                SetCell(cell, CellType::Border);
            }
            // If the cell is occupied by the snake, set it to Snake
            else if (m_pSnake->IsAtPosition(cell)) {
                SetCell(cell, CellType::Snake);
            }
            // Otherwise, add it to the set of empty positions
            else {
                m_emptyPositions.insert(cell);
            }
        }
    }

    // Add obstacles
    m_availableCells = ((m_gridWidth - 2) * (m_gridHeight - 2) -
                        (AddObstacles(obstacleCount) ? obstacleCount : 0)),

    // Add the first fruit
    AddFruit();
}

// Add obstacles to the game board
bool GameBoard::AddObstacles(unsigned int obstacleCount) {
    // Check if there are enough empty positions to add obstacles
    if (m_emptyPositions.size() < obstacleCount) {
        std::cout << "Not enough empty positions to add obstacles." << std::endl;
        return false;
    }

    // Add obstacles to random empty positions
    for (unsigned int i = 0; i < obstacleCount; ++i) {
        auto it = m_emptyPositions.begin();
        std::advance(it, rand() % m_emptyPositions.size());
        SetCell(*it, CellType::Obstacle);

        // Add the obstacle to the set of obstacles
        m_obstacles.insert(*it);
    }

    return true;
}

void GameBoard::SetCell(std::pair<unsigned int, unsigned int> cell, CellType type) {
    if (m_grid[cell.second][cell.first] != type) {

        // Remove the cell from the set of empty positions if it is currently empty
        if (m_grid[cell.second][cell.first] == CellType::Empty) {
            m_emptyPositions.erase(cell);
        }

        // Update the cell type
        m_grid[cell.second][cell.first] = type;

        // Add the cell to the set of empty positions if it is now empty
        if (type == CellType::Empty) {
            m_emptyPositions.insert(cell);
        }
    }
}

GameBoard::CellType GameBoard::GetCell(std::pair<unsigned int, unsigned int> cell) const {
    return m_grid[cell.second][cell.first];
}

bool GameBoard::Update() {
    bool fruitEaten = false;

    // Check if the snake has eaten the fruit
    if (m_pSnake->EatFruit(GetFruitPosition())) {
        fruitEaten = true;

        // Updated the last position of eaten fruit to Snake
        SetCell(GetFruitPosition(), CellType::Snake);

        // Add a new segment to the snake
        SetCell(m_pSnake->Move(true), CellType::Snake);

        // Generate a new fruit
        AddFruit();
    }
    else {
        std::pair<unsigned int, unsigned int> lastSnakeSegmentPosition = m_pSnake->GetLastSegment();

        // Move the snake in the updated direction
        SetCell(m_pSnake->Move(false), CellType::Snake);

        // Update the last position of the snake to Empty
        SetCell(lastSnakeSegmentPosition, CellType::Empty);
    }

    return fruitEaten;
}

void GameBoard::AddFruit() {
    // Check if there are any empty positions
    if (!m_emptyPositions.empty()) {
        // Select a random position from the set
        auto it = m_emptyPositions.begin();
        std::advance(it, rand() % m_emptyPositions.size());
        m_fruitPosition = *it;

        // Set the cell on the game board to be a fruit
        SetCell(GetFruitPosition(), CellType::Fruit);
    }
}

std::pair<unsigned int, unsigned int> GameBoard::GetFruitPosition() {
    return m_fruitPosition;
}

bool GameBoard::IsObstacle(std::pair<unsigned int, unsigned int> cell) const {
    // Check if the cell is in the set of obstacles
    return m_obstacles.find(cell) != m_obstacles.end();
}

const std::set<std::pair<unsigned int, unsigned int>>& GameBoard::GetObstacles() const {
    return m_obstacles;
}

unsigned int GameBoard::GetAvailableCells() const {
    return m_availableCells;
}
