#ifndef Player_hpp
#define Player_hpp

#include "AGameObject.hpp"
#include "Block.hpp"
#include "SDL.h"

class Player : public AGameObject {
public:
    Player(std::pair<double, double> pos, bool movable);
    virtual void update();
    virtual void handleEvent(SDL_Event event);
    virtual void draw(SDL_Renderer* renderer);
    // checks if player AND held block can move
    virtual bool move(std::pair<double, double> pos);
private:
    AGameObject * m_held; // the block the player is holding above its head
};

#endif