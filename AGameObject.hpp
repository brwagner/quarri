/**
   abstract class that represents an entity in the game world that can handle events, render itself to the screen based on its position, and update every frame.
 **/
#ifndef AGameObject_hpp
#define AGameObject_hpp

#include "SDL.h"
#include "Vector.hpp"

class AGameObject {
public:
  // update is called every frame
  virtual void update() = 0;
  // respond to events such as key input
  virtual void handleEvent(SDL_Event event) = 0;
  // render this GameObject to the screen
  virtual void draw(SDL_Renderer* renderer) = 0;
protected:
  // this GameObject's position in the game world
    Vector m_pos;
};

#endif
