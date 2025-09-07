#include "Snake.hpp"

Snake::Snake(Vector2 startPosition) 
    : currentDirection(Direction::RIGHT), 
      nextDirection(Direction::RIGHT),
      hasEaten(false) {
    body.push_back(startPosition);
    body.push_back(Vector2(startPosition.x - 1, startPosition.y));
    body.push_back(Vector2(startPosition.x - 2, startPosition.y));
}

void Snake::setDirection(Direction direction) {
    if (!isOppositeDirection(currentDirection, direction)) {
        nextDirection = direction;
    }
}

void Snake::update() {
    currentDirection = nextDirection;
    
    Vector2 newHead = body[0] + getDirectionVector(currentDirection);
    body.insert(body.begin(), newHead);
    
    if (!hasEaten) {
        body.pop_back();
    } else {
        hasEaten = false;
    }
}

void Snake::grow() {
    hasEaten = true;
}

bool Snake::checkSelfCollision() const {
    const Vector2& head = body[0];
    for (size_t i = 1; i < body.size(); ++i) {
        if (head == body[i]) {
            return true;
        }
    }
    return false;
}

bool Snake::checkWallCollision(int gridWidth, int gridHeight) const {
    const Vector2& head = body[0];
    return head.x < 0 || head.x >= gridWidth || 
           head.y < 0 || head.y >= gridHeight;
}

Vector2 Snake::getHeadPosition() const {
    return body[0];
}

const std::vector<Vector2>& Snake::getBody() const {
    return body;
}

size_t Snake::getLength() const {
    return body.size();
}

Vector2 Snake::getDirectionVector(Direction direction) const {
    switch (direction) {
        case Direction::UP:    return Vector2(0, -1);
        case Direction::DOWN:  return Vector2(0, 1);
        case Direction::LEFT:  return Vector2(-1, 0);
        case Direction::RIGHT: return Vector2(1, 0);
        default: return Vector2(0, 0);
    }
}

bool Snake::isOppositeDirection(Direction current, Direction next) const {
    return (current == Direction::UP && next == Direction::DOWN) ||
           (current == Direction::DOWN && next == Direction::UP) ||
           (current == Direction::LEFT && next == Direction::RIGHT) ||
           (current == Direction::RIGHT && next == Direction::LEFT);
}
