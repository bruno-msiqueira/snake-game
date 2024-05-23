// Utility.cpp
#include "Utility.h"

bool IsInSnakeBody(const std::vector<std::pair<int, int>>& body, const std::pair<int, int>& point) {
    for (const auto& segment : body) {
        if (segment.first == point.first && segment.second == point.second) {
            return true;
        }
    }
    return false;
}