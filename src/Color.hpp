#pragma once
#include <SDL.h>

struct Color {
    Uint8 r, g, b, a;
    
    Color(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255) 
        : r(r), g(g), b(b), a(a) {}
    
    static const Color BLACK;
    static const Color WHITE;
    static const Color GREEN;
    static const Color RED;
    static const Color BLUE;
    static const Color DARK_GREEN;
};
