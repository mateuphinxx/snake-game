#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer() 
    : window(nullptr), 
      renderer(nullptr), 
      font(nullptr),
      gridOffsetX(0),
      gridOffsetY(0) {}

Renderer::~Renderer() {
    cleanup();
}

bool Renderer::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    if (TTF_Init() < 0) {
        std::cerr << "TTF initialization failed: " << TTF_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("Snake Game", 
                              SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, 
                              WINDOW_HEIGHT, 
                              SDL_WINDOW_SHOWN);
    
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    font = TTF_OpenFont("assets/arial.ttf", 24);
    if (!font) {
        font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24);
        if (!font) {
            std::cerr << "Font loading failed, using default" << std::endl;
        }
    }
    
    gridOffsetX = (WINDOW_WIDTH - (20 * CELL_SIZE)) / 2;
    gridOffsetY = (WINDOW_HEIGHT - (15 * CELL_SIZE)) / 2;
    
    return true;
}

void Renderer::cleanup() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    
    TTF_Quit();
    SDL_Quit();
}

void Renderer::clear() {
    setColor(Color::BLACK);
    SDL_RenderClear(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}

void Renderer::renderGame(const Game& game) {
    clear();
    renderGrid(game.getGridWidth(), game.getGridHeight());
    renderSnake(game.getSnake());
    renderFood(game.getFood());
    
    if (game.getPowerUp().isActive()) {
        renderPowerUp(game.getPowerUp());
    }
    
    renderScore(game.getScore(), game.getHighScore());
    renderPowerUpStatus(game.isDoublePointsActive());
    present();
}

void Renderer::renderMenu() {
    clear();
    renderText("SNAKE GAME", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 100, Color::WHITE);
    renderText("Press SPACE to Start", WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 2 - 50, Color::WHITE);
    renderText("Use WASD or Arrow Keys to Move", WINDOW_WIDTH / 2 - 180, WINDOW_HEIGHT / 2, Color::WHITE);
    renderText("Press ESC to Quit", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 50, Color::WHITE);
    present();
}

void Renderer::renderGameOver(int score) {
    clear();
    renderText("GAME OVER", WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 - 100, Color::RED);
    renderText("Final Score: " + std::to_string(score), WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50, Color::WHITE);
    renderText("Press R to Restart", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, Color::WHITE);
    renderText("Press ESC to Quit", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 50, Color::WHITE);
    present();
}

void Renderer::renderPaused() {
    renderText("PAUSED", WINDOW_WIDTH / 2 - 50, 50, Color::WHITE);
    renderText("Press P to Resume", WINDOW_WIDTH / 2 - 100, 80, Color::WHITE);
}

void Renderer::setColor(const Color& color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Renderer::fillRect(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::drawRect(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::renderText(const std::string& text, int x, int y, const Color& color) {
    if (!font) return;
    
    SDL_Color sdlColor = {color.r, color.g, color.b, color.a};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), sdlColor);
    
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture) {
            SDL_Rect destRect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &destRect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

void Renderer::renderGrid(int gridWidth, int gridHeight) {
    setColor(Color::DARK_GREEN);
    
    for (int x = 0; x <= gridWidth; ++x) {
        int screenX = gridOffsetX + x * CELL_SIZE;
        SDL_RenderDrawLine(renderer, screenX, gridOffsetY, 
                          screenX, gridOffsetY + gridHeight * CELL_SIZE);
    }
    
    for (int y = 0; y <= gridHeight; ++y) {
        int screenY = gridOffsetY + y * CELL_SIZE;
        SDL_RenderDrawLine(renderer, gridOffsetX, screenY,
                          gridOffsetX + gridWidth * CELL_SIZE, screenY);
    }
}

void Renderer::renderSnake(const Snake& snake) {
    const auto& body = snake.getBody();
    
    for (size_t i = 0; i < body.size(); ++i) {
        Vector2 screenPos = gridToScreen(body[i]);
        
        if (i == 0) {
            setColor(Color::LIGHT_GREEN);
            fillRect(screenPos.x + 1, screenPos.y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
            setColor(Color::GREEN);
            drawRect(screenPos.x + 1, screenPos.y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
        } else {
            float intensity = 1.0f - (static_cast<float>(i) / body.size()) * 0.5f;
            Color segmentColor(
                static_cast<Uint8>(Color::GREEN.r * intensity),
                static_cast<Uint8>(Color::GREEN.g * intensity),
                static_cast<Uint8>(Color::GREEN.b * intensity)
            );
            setColor(segmentColor);
            fillRect(screenPos.x + 2, screenPos.y + 2, CELL_SIZE - 4, CELL_SIZE - 4);
        }
    }
}

void Renderer::renderFood(const Food& food) {
    Vector2 screenPos = gridToScreen(food.getPosition());
    setColor(Color::RED);
    fillRect(screenPos.x + 3, screenPos.y + 3, CELL_SIZE - 6, CELL_SIZE - 6);
    setColor(Color::ORANGE);
    fillRect(screenPos.x + 6, screenPos.y + 6, CELL_SIZE - 12, CELL_SIZE - 12);
}

void Renderer::renderPowerUp(const PowerUp& powerUp) {
    Vector2 screenPos = gridToScreen(powerUp.getPosition());
    
    Color powerUpColor;
    switch (powerUp.getType()) {
        case PowerUpType::DOUBLE_POINTS:
            powerUpColor = Color::GOLD;
            break;
        case PowerUpType::SPEED_BOOST:
            powerUpColor = Color::CYAN;
            break;
        case PowerUpType::SLOW_MOTION:
            powerUpColor = Color::PURPLE;
            break;
        case PowerUpType::GOLDEN_APPLE:
            powerUpColor = Color::YELLOW;
            break;
    }
    
    setColor(powerUpColor);
    fillRect(screenPos.x + 1, screenPos.y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
    setColor(Color::WHITE);
    drawRect(screenPos.x + 1, screenPos.y + 1, CELL_SIZE - 2, CELL_SIZE - 2);
}

void Renderer::renderScore(int score, int highScore) {
    renderText("Score: " + std::to_string(score), 10, 10, Color::WHITE);
    renderText("High Score: " + std::to_string(highScore), 10, 35, Color::GOLD);
}

void Renderer::renderPowerUpStatus(bool doublePointsActive) {
    if (doublePointsActive) {
        renderText("DOUBLE POINTS!", WINDOW_WIDTH - 200, 10, Color::GOLD);
    }
}

Vector2 Renderer::gridToScreen(const Vector2& gridPos) const {
    return Vector2(gridOffsetX + gridPos.x * CELL_SIZE, 
                   gridOffsetY + gridPos.y * CELL_SIZE);
}
