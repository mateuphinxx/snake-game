#include "Game.hpp"

Game::Game() 
    : currentState(GameState::MENU),
      score(0),
      gameSpeed(INITIAL_SPEED) {
    snake = std::make_unique<Snake>(Vector2(GRID_WIDTH / 2, GRID_HEIGHT / 2));
    food = std::make_unique<Food>(GRID_WIDTH, GRID_HEIGHT);
}

void Game::reset() {
    snake = std::make_unique<Snake>(Vector2(GRID_WIDTH / 2, GRID_HEIGHT / 2));
    food = std::make_unique<Food>(GRID_WIDTH, GRID_HEIGHT);
    score = 0;
    gameSpeed = INITIAL_SPEED;
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
        currentState = GameState::GAME_OVER;
        return;
    }
    
    handleFoodCollision();
}

void Game::handleFoodCollision() {
    if (snake->getHeadPosition() == food->getPosition()) {
        snake->grow();
        score += 10;
        
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

int Game::getScore() const {
    return score;
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
