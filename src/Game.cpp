#include "Game.hpp"

Game::Game() 
    : currentState(GameState::MENU),
      score(0),
      highScore(0),
      gameSpeed(INITIAL_SPEED),
      powerUpTimer(0),
      doublePointsActive(false),
      doublePointsTimer(0) {
    snake = std::make_unique<Snake>(Vector2(GRID_WIDTH / 2, GRID_HEIGHT / 2));
    food = std::make_unique<Food>(GRID_WIDTH, GRID_HEIGHT);
    powerUp = std::make_unique<PowerUp>(GRID_WIDTH, GRID_HEIGHT);
    soundManager = std::make_unique<SoundManager>();
    soundManager->initialize();
    powerUp->setActive(false);
}

void Game::reset() {
    snake = std::make_unique<Snake>(Vector2(GRID_WIDTH / 2, GRID_HEIGHT / 2));
    food = std::make_unique<Food>(GRID_WIDTH, GRID_HEIGHT);
    powerUp = std::make_unique<PowerUp>(GRID_WIDTH, GRID_HEIGHT);
    
    if (score > highScore) {
        highScore = score;
    }
    
    score = 0;
    gameSpeed = INITIAL_SPEED;
    powerUpTimer = 0;
    doublePointsActive = false;
    doublePointsTimer = 0;
    powerUp->setActive(false);
    currentState = GameState::PLAYING;
}

void Game::startGame() {
    reset();
}

void Game::update() {
    if (currentState != GameState::PLAYING) {
        return;
    }
    
    snake->update();
    
    if (snake->checkWallCollision(GRID_WIDTH, GRID_HEIGHT) || 
        snake->checkSelfCollision()) {
        soundManager->playSound("game_over");
        currentState = GameState::GAME_OVER;
        return;
    }
    
    handleFoodCollision();
    handlePowerUpCollision();
    updatePowerUps();
}

void Game::handleFoodCollision() {
    if (snake->getHeadPosition() == food->getPosition()) {
        snake->grow();
        
        int points = doublePointsActive ? 20 : 10;
        score += points;
        
        soundManager->playSound("eat");
        
        if (gameSpeed > 50) {
            gameSpeed -= 2;
        }
        
        Vector2 newFoodPos;
        bool validPosition = false;
        
        while (!validPosition) {
            food->generateNew(GRID_WIDTH, GRID_HEIGHT);
            newFoodPos = food->getPosition();
            validPosition = true;
            
            for (const auto& segment : snake->getBody()) {
                if (segment == newFoodPos) {
                    validPosition = false;
                    break;
                }
            }
            
            if (powerUp->isActive() && newFoodPos == powerUp->getPosition()) {
                validPosition = false;
            }
        }
        
        powerUpTimer++;
        if (powerUpTimer >= 5 && !powerUp->isActive() && powerUp->shouldSpawn()) {
            Vector2 powerUpPos;
            bool validPowerUpPos = false;
            
            while (!validPowerUpPos) {
                powerUp->generateNew(GRID_WIDTH, GRID_HEIGHT);
                powerUpPos = powerUp->getPosition();
                validPowerUpPos = true;
                
                for (const auto& segment : snake->getBody()) {
                    if (segment == powerUpPos) {
                        validPowerUpPos = false;
                        break;
                    }
                }
                
                if (powerUpPos == food->getPosition()) {
                    validPowerUpPos = false;
                }
            }
            powerUpTimer = 0;
        }
    }
}

void Game::handlePowerUpCollision() {
    if (powerUp->isActive() && snake->getHeadPosition() == powerUp->getPosition()) {
        soundManager->playSound("powerup");
        
        switch (powerUp->getType()) {
            case PowerUpType::DOUBLE_POINTS:
                doublePointsActive = true;
                doublePointsTimer = 300;
                break;
            case PowerUpType::SPEED_BOOST:
                gameSpeed = std::max(50, gameSpeed - 30);
                break;
            case PowerUpType::SLOW_MOTION:
                gameSpeed = std::min(200, gameSpeed + 50);
                break;
            case PowerUpType::GOLDEN_APPLE:
                score += doublePointsActive ? 100 : 50;
                break;
        }
        
        powerUp->setActive(false);
    }
}

void Game::updatePowerUps() {
    if (doublePointsActive) {
        doublePointsTimer--;
        if (doublePointsTimer <= 0) {
            doublePointsActive = false;
        }
    }
}

bool Game::isGameOver() const {
    return currentState == GameState::GAME_OVER;
}

GameState Game::getState() const {
    return currentState;
}

void Game::setState(GameState state) {
    currentState = state;
}

const Snake& Game::getSnake() const {
    return *snake;
}

Snake& Game::getSnake() {
    return *snake;
}

const Food& Game::getFood() const {
    return *food;
}

const PowerUp& Game::getPowerUp() const {
    return *powerUp;
}

SoundManager& Game::getSoundManager() {
    return *soundManager;
}

int Game::getScore() const {
    return score;
}

int Game::getHighScore() const {
    return highScore;
}

int Game::getGridWidth() const {
    return GRID_WIDTH;
}

int Game::getGridHeight() const {
    return GRID_HEIGHT;
}

int Game::getGameSpeed() const {
    return gameSpeed;
}

bool Game::isDoublePointsActive() const {
    return doublePointsActive;
}
