#ifndef LevelState_hpp
#define LevelState_hpp

#include "SDL.h"
#include <utility>
#include <map>
#include <vector>

#include "Display.hpp"

// Forward declarations to prevent cycles
class AGameObject;
class Display;

class LevelState {
public:
    LevelState(std::vector<AGameObject*>* gameObjects);
    // returns object at the given position, or null if none can be found
    // should use isObjectAtPosition to check for validity before using
    AGameObject* getAtPosition(const std::pair<double,double> pos);
    // changes the key of from to to if to is not already a key
    bool move(std::pair<double, double> from, std::pair<double, double> to);
    // checks for GameObject at that position
    bool isAtPosition(const std::pair<double,double> pos);
    // calls update on each GameObject in the map
    void update();
    // renders the GameObjects using the given display
    void renderTo(Display* display);
    // passes events down to each GameObject
    void handleEvent(SDL_Event event);
private:
    std::map<std::pair<double, double>, AGameObject*> m_level_map;
};

#endif
