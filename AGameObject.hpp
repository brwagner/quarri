#ifndef AGameObject_hpp
#define AGameObject_hpp

#include "SDL.h"
#include "Vector.hpp"

class AGameObject {
public:
    virtual void update() = 0;
    virtual void handleEvent(SDL_Event event) = 0;
    virtual void draw(SDL_Renderer* renderer) = 0;
protected:
    Vector m_pos;
};

#endif