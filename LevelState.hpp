#ifndef LevelState_hpp
#define LevelState_hpp

#include "SDL.h"
#include <utility>
#include <map>
#include <string>
#include <vector>

#include "Display.hpp"

// Forward declarations to prevent cycles
class AGameObject;
class Display;

class LevelState {
public:
    // specify the path to load levels from
    LevelState(std::string level_res_path);
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
    // loads the level in the res folder
    void loadLevel(int level_index);
private:
    std::map<std::pair<double, double>, AGameObject*> m_level_map;
    std::string m_level_res_path;
    void clear();
};

#endif
