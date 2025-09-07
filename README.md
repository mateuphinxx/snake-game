# Snake Game

Basic Snake game built with C++ and SDL2 for learning purposes.

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

## Controls

- **WASD/Arrow Keys**: Move
- **SPACE**: Start
- **P**: Pause
- **R**: Restart
- **ESC**: Exit
