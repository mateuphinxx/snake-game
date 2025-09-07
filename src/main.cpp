#include "Game.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include <SDL.h>
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    Game game;
    Renderer renderer;
    InputHandler inputHandler;
    
    if (!renderer.initialize()) {
        return -1;
    }
    
    bool running = true;
    auto lastUpdateTime = std::chrono::steady_clock::now();
    
    while (running) {
        auto currentTime = std::chrono::steady_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - lastUpdateTime).count();
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            InputHandler::Action action = inputHandler.handleInput(event, game.getState());
            
            switch (action) {
                case InputHandler::Action::QUIT:
                    running = false;
                    break;
                    
                case InputHandler::Action::START_GAME:
                    if (game.getState() == GameState::MENU) {
                        game.startGame();
                    }
                    break;
                    
                case InputHandler::Action::RESTART_GAME:
                    if (game.getState() == GameState::GAME_OVER) {
                        game.startGame();
                    }
                    break;
                    
                case InputHandler::Action::PAUSE_TOGGLE:
                    if (game.getState() == GameState::PLAYING) {
                        game.setState(GameState::PAUSED);
                    } else if (game.getState() == GameState::PAUSED) {
                        game.setState(GameState::PLAYING);
                    }
                    break;
                    
                case InputHandler::Action::MOVE_UP:
                case InputHandler::Action::MOVE_DOWN:
                case InputHandler::Action::MOVE_LEFT:
                case InputHandler::Action::MOVE_RIGHT:
                    if (game.getState() == GameState::PLAYING) {
                        game.getSnake().setDirection(inputHandler.getDirectionFromAction(action));
                    }
                    break;
                    
                default:
                    break;
            }
        }
        
        if (game.getState() == GameState::PLAYING && deltaTime >= game.getGameSpeed()) {
            game.update();
            lastUpdateTime = currentTime;
        }
        
        switch (game.getState()) {
            case GameState::MENU:
                renderer.renderMenu();
                break;
                
            case GameState::PLAYING:
                renderer.renderGame(game);
                break;
                
            case GameState::PAUSED:
                renderer.renderGame(game);
                renderer.renderPaused();
                renderer.present();
                break;
                
            case GameState::GAME_OVER:
                renderer.renderGameOver(game.getScore());
                break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    
    return 0;
}
