#pragma once
#include "Vector2.hpp"
#include "PowerUpType.hpp"
#include <random>

class PowerUp {
private:
    Vector2 position;
    PowerUpType type;
    int duration;
    bool active;
    std::mt19937 rng;
    std::uniform_int_distribution<int> xDist;
    std::uniform_int_distribution<int> yDist;
    std::uniform_int_distribution<int> typeDist;

public:
    PowerUp(int gridWidth, int gridHeight);
    void generateNew(int gridWidth, int gridHeight);
    void setActive(bool isActive);
    
    Vector2 getPosition() const;
    PowerUpType getType() const;
    int getDuration() const;
    bool isActive() const;
    
    void update();
    bool shouldSpawn() const;

private:
    PowerUpType generateRandomType();
};
