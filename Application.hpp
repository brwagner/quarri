#ifndef Application_hpp
#define Application_hpp

#include "SDL.h"
#include <vector>
#include "AGameObject.hpp"

/** represents an instance of the game
keeps track of all gameobjects
**/

class Application {
public:
    // called once when the game first starts
    // initializes gameobjects and game world
    // then runs an update loop until game ends
    void start();
};

#endif
