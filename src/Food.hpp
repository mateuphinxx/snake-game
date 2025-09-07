#pragma once
#include "Vector2.hpp"
#include <random>

class Food {
private:
    Vector2 position;
    std::mt19937 rng;
    std::uniform_int_distribution<int> xDist;
    std::uniform_int_distribution<int> yDist;

public:
    Food(int gridWidth, int gridHeight);
    void generateNew(int gridWidth, int gridHeight);
    Vector2 getPosition() const;
};
