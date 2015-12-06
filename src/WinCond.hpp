#ifndef WinCond_hpp
#define WinCond_hpp

#include "Block.hpp"
#include "SDL.h"

class WinCond : public Block {
public:
    WinCond(std::pair<double, double> pos);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer, int xOff);
};

#endif