#pragma once
#include "Direction.hpp"
#include "Game.hpp"
#include <SDL.h>

class InputHandler {
public:
    enum class Action {
        NONE,
        QUIT,
        START_GAME,
        RESTART_GAME,
        PAUSE_TOGGLE,
        MOVE_UP,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT
    };
    
    Action handleInput(const SDL_Event& event, GameState currentState);
    Direction getDirectionFromAction(Action action);
    
private:
    Action getActionFromKey(SDL_Keycode key, GameState currentState);
};
