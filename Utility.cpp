// Utility.cpp
#include "Utility.h"
#include <cstdlib> // for getenv

bool IsInSnakeBody(const std::vector<std::pair<int, int>>& body, const std::pair<int, int>& point) {
    for (const auto& segment : body) {
        if (segment.first == point.first && segment.second == point.second) {
            return true;
        }
    }
    return false;
}

std::string GetClearCommand() {
    char* term = std::getenv("TERM");
    char* comspec = std::getenv("ComSpec");

    if (comspec != nullptr) {
        // We're likely on Windows, so use 'cls'
        return "cls";
    } else if (term != nullptr && std::string(term) == "xterm") {
        // We're likely on Unix and using an xterm-compatible terminal, so use 'clear'
        return "clear";
    } else {
        // Default to 'clear' if we're unsure
        return "clear";
    }
}