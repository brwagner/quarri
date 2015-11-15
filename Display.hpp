#ifndef Display_hpp
#define Display_hpp

#include "SDL.h"
#include "AGameObject.hpp"
#include <vector>

/**
creates a window for the application and renders the game state to that window
 **/
class Display {
public:
  // create a window with the given title, width, and height
  // initialize the renderer to use the window
  Display(const char * name, int width, int height);
  // draws all gameobjects to the screen
  void render(const std::vector<AGameObject*> & level);
    ~Display();
private:
  // the width of the window
  int m_width;
  // the height of the window
  int m_height;
  // the renderer used to draw to the screen
  SDL_Renderer* m_renderer;
  // the application window
  SDL_Window* m_window;
};

#endif
