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
    LevelState(std::string level_res_path, int current_level, Display* display);
    // returns object at the given position, or null if none can be found
    // should use isObjectAtPosition to check for validity before using
    AGameObject* getAtPosition(const std::pair<double,double> pos);
    // changes the key of from to to if to is not already a key
    bool move(std::pair<double, double> from, std::pair<double, double> to);
    // checks for GameObject at that position
    bool isAtPosition(const std::pair<double,double> pos);
    // calls update on each GameObject in the map
    void update();
    // renders the GameObjects using the displayed stored as a pointer
    void renderToDisplay();
    // passes events down to each GameObject
    void handleEvent(SDL_Event event);
    // registers that the player won
    void registerWin();
    // moves the camera left or right the given amount
    void moveCamera(int xOff);
private:
    // deletes gameobjects and clears the map
    void clear();
    // loads the level in the res folder
    void loadLevel(int level_index);
    // sometimes we need to keep a copy if we're deleting and iterating
    std::vector< std::pair<std::pair<double,double>, AGameObject*> > getKeyValueList();
    // sometimes we need to pass a value list to the renderer
    std::vector<AGameObject*> getValueList();
    // represents the underlying state of the level
    std::map<std::pair<double, double>, AGameObject*> m_level_map;
    // path for loading levels by number
    std::string m_level_res_path;
    // the number of the current level
    int m_current_level;
    // should we load the next level
    bool m_should_load;
    // A pointer to the display for the game
    Display * m_display;
};

#endif
