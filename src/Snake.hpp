#pragma once
#include "Vector2.hpp"
#include "Direction.hpp"
#include <vector>

class Snake {
private:
    std::vector<Vector2> body;
    Direction currentDirection;
    Direction nextDirection;
    bool hasEaten;

public:
    Snake(Vector2 startPosition);
    void setDirection(Direction direction);
    void update();
    void grow();
    bool checkSelfCollision() const;
    bool checkWallCollision(int gridWidth, int gridHeight) const;
    Vector2 getHeadPosition() const;
    const std::vector<Vector2>& getBody() const;
    size_t getLength() const;

private:
    Vector2 getDirectionVector(Direction direction) const;
    bool isOppositeDirection(Direction current, Direction next) const;
};
