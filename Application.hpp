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
private:
  // pass a given event to all gameobjects in the level
  void handleGameEvents(SDL_Event event, const std::vector<AGameObject*> & level);
  // call update on every gameobject in the level  
  void update(const std::vector<AGameObject*> & level);
};

#endif
