#ifndef Player_hpp
#define Player_hpp

#include "AGameObject.hpp"
#include "SDL.h"

class Player : public AGameObject {
public:
    virtual void update();
    virtual void handleEvent(SDL_Event event);
    virtual void draw(SDL_Renderer* renderer);
};

#endif