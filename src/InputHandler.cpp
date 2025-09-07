#include "InputHandler.hpp"

InputHandler::Action InputHandler::handleInput(const SDL_Event& event, GameState currentState) {
    if (event.type == SDL_QUIT) {
        return Action::QUIT;
    }
    
    if (event.type == SDL_KEYDOWN) {
        return getActionFromKey(event.key.keysym.sym, currentState);
    }
    
    return Action::NONE;
}

Direction InputHandler::getDirectionFromAction(Action action) {
    switch (action) {
        case Action::MOVE_UP:    return Direction::UP;
        case Action::MOVE_DOWN:  return Direction::DOWN;
        case Action::MOVE_LEFT:  return Direction::LEFT;
        case Action::MOVE_RIGHT: return Direction::RIGHT;
        default: return Direction::UP;
    }
}

InputHandler::Action InputHandler::getActionFromKey(SDL_Keycode key, GameState currentState) {
    switch (key) {
        case SDLK_ESCAPE:
            return Action::QUIT;
            
        case SDLK_SPACE:
            if (currentState == GameState::MENU) {
                return Action::START_GAME;
            }
            break;
            
        case SDLK_r:
            if (currentState == GameState::GAME_OVER) {
                return Action::RESTART_GAME;
            }
            break;
            
        case SDLK_p:
            if (currentState == GameState::PLAYING || currentState == GameState::PAUSED) {
                return Action::PAUSE_TOGGLE;
            }
            break;
            
        case SDLK_w:
        case SDLK_UP:
            if (currentState == GameState::PLAYING) {
                return Action::MOVE_UP;
            }
            break;
            
        case SDLK_s:
        case SDLK_DOWN:
            if (currentState == GameState::PLAYING) {
                return Action::MOVE_DOWN;
            }
            break;
            
        case SDLK_a:
        case SDLK_LEFT:
            if (currentState == GameState::PLAYING) {
                return Action::MOVE_LEFT;
            }
            break;
            
        case SDLK_d:
        case SDLK_RIGHT:
            if (currentState == GameState::PLAYING) {
                return Action::MOVE_RIGHT;
            }
            break;
    }
    
    return Action::NONE;
}
