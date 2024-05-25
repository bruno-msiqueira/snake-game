#include "Snake.hpp"

// Constructor initializes the snake.
Snake::Snake(unsigned int gridWidth, unsigned int gridHeight) {
    // Initialize snake with one segment at the center of the grid
    m_segments.push_back(std::make_pair(gridWidth / 2, gridHeight / 2));
}

// GetSize returns the size of the snake.
unsigned int Snake::GetSize() const {
    return m_segments.size();
}

// GetSegments returns the segments of the snake.
const std::vector<std::pair<unsigned int, unsigned int>>& Snake::GetSegments() const {
    return m_segments;
}

std::pair<unsigned int, unsigned int> Snake::GetHead() const {
    return m_segments.front();
}

std::pair<unsigned int, unsigned int> Snake::GetTail() const{
    return m_segments.back();
}

bool Snake::IsAtPosition(const std::pair<unsigned int, unsigned int>& position) const {
    for (const auto& segment : m_segments) {
        if (segment == position) {
            return true;
        }
    }
    return false;
}

std::pair<unsigned int, unsigned int> Snake::Move(const std::pair<unsigned int, unsigned int>& nextPosition, bool grow) {
    std::pair<unsigned int, unsigned int> tailPositionBeforeMove = m_segments.back();

    if (!grow) {
        m_segments.pop_back();
    }

    // Move the snake to the next position
    m_segments.insert(m_segments.begin(), nextPosition);

    return tailPositionBeforeMove;
}