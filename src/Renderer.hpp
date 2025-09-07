#pragma once
#include "Vector2.hpp"
#include "Color.hpp"
#include "Game.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <string>

class Renderer {
private:
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
    static constexpr int CELL_SIZE = 30;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    
    int gridOffsetX;
    int gridOffsetY;
    
public:
    Renderer();
    ~Renderer();
    
    bool initialize();
    void cleanup();
    void clear();
    void present();
    
    void renderGame(const Game& game);
    void renderMenu();
    void renderGameOver(int score);
    void renderPaused();
    
private:
    void setColor(const Color& color);
    void fillRect(int x, int y, int width, int height);
    void drawRect(int x, int y, int width, int height);
    void renderText(const std::string& text, int x, int y, const Color& color);
    void renderGrid(int gridWidth, int gridHeight);
    void renderSnake(const Snake& snake);
    void renderFood(const Food& food);
    void renderPowerUp(const PowerUp& powerUp);
    void renderScore(int score, int highScore);
    void renderPowerUpStatus(bool doublePointsActive);
    Vector2 gridToScreen(const Vector2& gridPos) const;
};
