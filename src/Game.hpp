#pragma once
#include "Snake.hpp"
#include "Food.hpp"
#include "PowerUp.hpp"
#include "GameState.hpp"
#include "SoundManager.hpp"
#include <memory>

class Game {
private:
    static constexpr int GRID_WIDTH = 20;
    static constexpr int GRID_HEIGHT = 15;
    static constexpr int INITIAL_SPEED = 150;
    
    std::unique_ptr<Snake> snake;
    std::unique_ptr<Food> food;
    std::unique_ptr<PowerUp> powerUp;
    std::unique_ptr<SoundManager> soundManager;
    GameState currentState;
    int score;
    int highScore;
    int gameSpeed;
    int powerUpTimer;
    bool doublePointsActive;
    int doublePointsTimer;
    
public:
    Game();
    void reset();
    void startGame();
    void update();
    void handleFoodCollision();
    void handlePowerUpCollision();
    void updatePowerUps();
    bool isGameOver() const;
    
    GameState getState() const;
    void setState(GameState state);
    const Snake& getSnake() const;
    Snake& getSnake();
    const Food& getFood() const;
    const PowerUp& getPowerUp() const;
    SoundManager& getSoundManager();
    int getScore() const;
    int getHighScore() const;
    int getGridWidth() const;
    int getGridHeight() const;
    int getGameSpeed() const;
    bool isDoublePointsActive() const;
};
