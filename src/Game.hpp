#pragma once
#include "Snake.hpp"
#include "Food.hpp"
#include "GameState.hpp"
#include <memory>

class Game {
private:
    static constexpr int GRID_WIDTH = 20;
    static constexpr int GRID_HEIGHT = 15;
    static constexpr int INITIAL_SPEED = 150;
    
    std::unique_ptr<Snake> snake;
    std::unique_ptr<Food> food;
    GameState currentState;
    int score;
    int gameSpeed;
    
public:
    Game();
    void reset();
    void startGame();
    void update();
    void handleFoodCollision();
    bool isGameOver() const;
    
    GameState getState() const;
    void setState(GameState state);
    const Snake& getSnake() const;
    Snake& getSnake();
    const Food& getFood() const;
    int getScore() const;
    int getGridWidth() const;
    int getGridHeight() const;
    int getGameSpeed() const;
};
