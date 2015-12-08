#ifndef Display_hpp
#define Display_hpp

#include "SDL.h"
#include "AGameObject.hpp"
#include <vector>

// Forward declaration to prevent cycles
class AGameObject;

/**
creates a window for the application and renders the game state to that window
 **/
class Display {
public:
    // create a window with the given title, width, and height
    // initialize the renderer to use the window
    Display(const char * name, int width, int height);
    // draws all gameobjects to the screen
    void render(std::vector<AGameObject*> * level);
    // cleans up the window and renderer components
    ~Display();
    // Moves the camera to the left or right
    void moveCamera(int xOff);
    // sets offset to zero
    void resetCamera();
    
    // new methods only used by tests
    // gets the camera offset
    int getCameraOffset();
    //gets the width
    int getWidth();
    // gets the height
    int getHeight();

private:
    // the width of the window
    int m_width;
    // the height of the window
    int m_height;
    // the renderer used to draw to the screen
    SDL_Renderer* m_renderer;
    // the application window
    SDL_Window* m_window;
    //The cameraOffset
    int m_cameraOffX;
};

#endif
