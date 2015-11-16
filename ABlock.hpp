#ifndef ABlock_hpp
#define ABlock_hpp

#include "AGameObject.hpp"

class ABlock : public AGameObject {
public:
    virtual bool isMovable() = 0;
    virtual int getColor() = 0;
    virtual void update();
    virtual void handleEvent(SDL_Event event);
    virtual void draw(SDL_Renderer* renderer);
};

#endif
