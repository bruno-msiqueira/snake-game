#include "Snake.hpp"

// Constructor initializes the snake.
Snake::Snake(int gridWidth, int gridHeight) : m_gridWidth(gridWidth), m_gridHeight(gridHeight) {
    // Initialize snake with one segment at the center of the grid
    m_segments.push_back(std::make_pair(gridWidth / 2, gridHeight / 2));
    m_direction = Direction::RIGHT; // Start moving to the right
}

// GetSegments returns the segments of the snake.
const std::vector<std::pair<unsigned int, unsigned int>>& Snake::GetSegments() const {
    return m_segments;
}

std::pair<unsigned int, unsigned int> Snake::GetLastSegment() const{
    return m_segments.back();
}

void Snake::SetDirection(Direction dir) {
    m_direction = dir;
}

Snake::Direction Snake::GetDirection() const {
    return m_direction;
}

// GetNextPosition returns the next position of the snake head based on the current direction.
std::pair<unsigned int, unsigned int> Snake::GetNextPosition() const {
    std::pair<unsigned int, unsigned int> next_position = m_segments[0];

    switch (m_direction) {
    case Direction::UP:
        next_position.second--;
        break;
    case Direction::DOWN:
        next_position.second++;
        break;
    case Direction::LEFT:
        next_position.first--;
        break;
    case Direction::RIGHT:
        next_position.first++;
        break;
    }

    return next_position;
}

std::pair<unsigned int, unsigned int> Snake::Move(bool fruitEaten) {
    return Move(GetDirection(), fruitEaten);
}

// Move moves the snake in the current direction.
std::pair<unsigned int, unsigned int> Snake::Move(Direction dir, bool fruitEaten) {
    // Get the next position based on the current direction
    std::pair<unsigned int, unsigned int> next_position = GetNextPosition();

    // Move the snake to the next position
    m_segments.insert(m_segments.begin(), next_position);
    if (!fruitEaten) {
        m_segments.pop_back();
    }

    return next_position;
}

bool Snake::SelfHit() const {
    auto head = m_segments.front();

    // The game is also over if the snake has collided with itself
    for (auto it = m_segments.begin() + 1; it != m_segments.end(); ++it) {
        if (*it == head) {
            return true;
        }
    }
    return false;
}

bool Snake::WallHit() const {
    // The game is over if the snake has moved out of bounds
    auto head = m_segments.front();
    return (head.first == 0  || head.first >= m_gridWidth - 1 ||
            head.second == 0 || head.second >= m_gridHeight - 1);
}

bool Snake::EatFruit(const std::pair<unsigned int, unsigned int> fruitPosition) {
    if (GetNextPosition() == fruitPosition) {
        return true;
    }
    return false;
}

bool Snake::IsPositionOccupied(const std::pair<unsigned int, unsigned int>& position) const {
    for (const auto& segment : m_segments) {
        if (segment == position) {
            return true;
        }
    }
    return false;
}

bool Snake::IsAtPosition(const std::pair<unsigned int, unsigned int>& position) const {
    for (const auto& segment : m_segments) {
        if (segment == position) {
            return true;
        }
    }
    return false;
}

std::pair<unsigned int, unsigned int> Snake::GetHead() const {
    return m_segments.front();
}