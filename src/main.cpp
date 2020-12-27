#include <iostream>
#include "maze/maze.hpp"

int main() {
    maze m{5, 5};       // 5x5 maze
    for (const auto& conn : m.generate()) {
        std::cout << conn.first.first << " " << conn.first.second << " to ";
        std::cout << conn.second.first << " " << conn.second.second << std::endl;
    }
    return 0;
}
