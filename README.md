# Snake Game

Snake game built with C++ and SDL2, sound effects, and improved visuals.

## Requirements

- C++17 compiler
- CMake 3.15+
- Conan 2.0+

## Build

```bash
pip install conan
conan profile detect --force
conan install . --build=missing
cmake --preset default
cmake --build build --config Release
```

## Run

```bash
./build/Release/SnakeGame.exe
```

## Features

- Classic Snake gameplay with enhanced visuals
- **Power-ups**: Double Points, Speed Boost, Slow Motion, Golden Apple
- **Sound effects** for eating, power-ups, and game over
- **High score** tracking
- Gradient snake body with visual improvements

## Controls

- **WASD/Arrow Keys**: Move
- **SPACE**: Start
- **P**: Pause
- **R**: Restart
- **ESC**: Exit

## Power-ups

- **Golden Apple**: Instant bonus points
- **Speed Boost**: Increases snake speed temporarily  
- **Slow Motion**: Decreases snake speed temporarily
- **Double Points**: All food gives double points for limited time
