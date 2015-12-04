#ifndef Player_hpp
#define Player_hpp

#include "AGameObject.hpp"
#include "Block.hpp"
#include "SDL.h"
#include "SDL_mixer.h"

class Player : public AGameObject {
public:
    Player(std::pair<double, double> pos, bool movable);
    ~Player(); // Cleanup music resources
    virtual void update();
    virtual void handleEvent(SDL_Event event);
    virtual void draw(SDL_Renderer* renderer, int xOff);
    // checks if player AND held block can move
    virtual bool move(std::pair<double, double> pos);
private:
    // sound effects for moving
    Mix_Chunk* m_boop_sound;
    Mix_Chunk* m_woosh_sound;
    // gets position that the player would move to if they moved forward
    std::pair<double, double> forwardPos();
    // gets position that the player would move to if they moved up and forward
    std::pair<double, double> forwardUpPos();
    // check if the event corresponds to a movement event
    bool isMoving(SDL_Event event);
    // check if we're moving the direction we're facing
    bool isMovingTowardsDir(SDL_Event event);
    // check pickup bounds
    bool isPickupValid();
    // direction of the player
    int m_dir;
    // the block the player is holding above its head
    AGameObject * m_held;
};

#endif
