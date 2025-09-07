#include "Food.hpp"

Food::Food(int gridWidth, int gridHeight) 
    : rng(std::random_device{}()), 
      xDist(0, gridWidth - 1), 
      yDist(0, gridHeight - 1) {
    generateNew(gridWidth, gridHeight);
}

void Food::generateNew(int gridWidth, int gridHeight) {
    xDist = std::uniform_int_distribution<int>(0, gridWidth - 1);
    yDist = std::uniform_int_distribution<int>(0, gridHeight - 1);
    position = Vector2(xDist(rng), yDist(rng));
}

Vector2 Food::getPosition() const {
    return position;
}
