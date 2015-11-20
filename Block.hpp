#ifndef Block_hpp
#define Block_hpp

#include "AGameObject.hpp"

class Block : public AGameObject {
public:
    Block(std::pair<double, double> pos, bool movable, int color);
    virtual void update();
    virtual void handleEvent(SDL_Event event);
    virtual void draw(SDL_Renderer* renderer);
private:
    int m_color;
};

#endif
