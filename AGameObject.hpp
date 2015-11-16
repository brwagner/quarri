#ifndef AGameObject_hpp
#define AGameObject_hpp

#include "SDL.h"
#include <utility>

class AGameObject {
public:
    virtual void update() = 0;
    virtual void handleEvent(SDL_Event event) = 0;
    virtual void draw(SDL_Renderer* renderer) = 0;
    const std::pair<double, double> getPos() { return m_pos; }
    void setPos(std::pair<double, double> newPos) { m_pos = newPos; }
protected:
    std::pair<double,double> m_pos;
};

#endif