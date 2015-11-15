#ifndef Display_hpp
#define Display_hpp

#include "SDL.h"
#include "AGameObject.hpp"
#include <vector>

class Display {
public:
    Display(const char * name, int width, int height);
    void render(const std::vector<AGameObject*> & level);
    ~Display();
private:
    int m_width;
    int m_height;
    SDL_Renderer* m_renderer;
    SDL_Window* m_window;
};

#endif
