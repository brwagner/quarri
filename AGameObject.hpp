/**
   abstract class that represents an entity in the game world that can handle events, render itself to the screen based on its position, and update every frame.
 **/
#ifndef AGameObject_hpp
#define AGameObject_hpp

#include "SDL.h"
#include <utility>

#include "LevelState.hpp"

// Forward declaration to prevent cycles
class LevelState;

class AGameObject {
public:
    AGameObject(std::pair<double, double> pos, bool movable, bool player);
    virtual ~AGameObject() {}
    // update is called every frame
    virtual void update() = 0;
    // respond to events such as key input
    virtual void handleEvent(SDL_Event event) = 0;
    // render this GameObject to the screen
    virtual void draw(SDL_Renderer* renderer) = 0;
    // checks if there's already someone in the position
    // update's position in the GameObject and LevelState
    // returns true if the move was successful
    bool move(std::pair<double, double> pos);
    // helpers for directions
    std::pair<double, double> relativePosition(int x, int y);
    std::pair<double, double> up();
    std::pair<double, double> down();
    std::pair<double, double> left();
    std::pair<double, double> right();
    // getters and setters
    void setLevelState(LevelState * level_state);
    const std::pair<double, double> getPos() const;
    const bool isMovable() const;
    const bool isPlayer() const;
protected:
    // a reference to other gameobejcts
    LevelState * m_level_state;
private:
    // this GameObject's position in the game world
    std::pair<double,double> m_pos;
    // can this be picked up?
    bool m_movable;
    // is this the player
    bool m_player;
};

#endif
