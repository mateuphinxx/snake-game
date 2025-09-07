#include "PowerUp.hpp"

PowerUp::PowerUp(int gridWidth, int gridHeight) 
    : rng(std::random_device{}()), 
      xDist(0, gridWidth - 1), 
      yDist(0, gridHeight - 1),
      typeDist(0, 3),
      active(false),
      duration(0) {
    generateNew(gridWidth, gridHeight);
}

void PowerUp::generateNew(int gridWidth, int gridHeight) {
    xDist = std::uniform_int_distribution<int>(0, gridWidth - 1);
    yDist = std::uniform_int_distribution<int>(0, gridHeight - 1);
    position = Vector2(xDist(rng), yDist(rng));
    type = generateRandomType();
    
    switch (type) {
        case PowerUpType::DOUBLE_POINTS:
            duration = 300;
            break;
        case PowerUpType::SPEED_BOOST:
            duration = 200;
            break;
        case PowerUpType::SLOW_MOTION:
            duration = 250;
            break;
        case PowerUpType::GOLDEN_APPLE:
            duration = 0;
            break;
    }
    
    active = true;
}

void PowerUp::setActive(bool isActive) {
    active = isActive;
}

Vector2 PowerUp::getPosition() const {
    return position;
}

PowerUpType PowerUp::getType() const {
    return type;
}

int PowerUp::getDuration() const {
    return duration;
}

bool PowerUp::isActive() const {
    return active;
}

void PowerUp::update() {
    if (duration > 0) {
        duration--;
        if (duration <= 0) {
            active = false;
        }
    }
}

bool PowerUp::shouldSpawn() const {
    static std::mt19937 spawnRng(std::random_device{}());
    static std::uniform_int_distribution<int> spawnChance(1, 100);
    
    return spawnChance(spawnRng) <= 15;
}

PowerUpType PowerUp::generateRandomType() {
    return static_cast<PowerUpType>(typeDist(rng));
}
