#include "Display.hpp"

Display::Display(const char * name, int width, int height) : m_width(width), m_height(height) {
    m_window = SDL_CreateWindow("Quarri",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_SHOWN);
    
    m_renderer = SDL_CreateRenderer(m_window, 0, SDL_RENDERER_ACCELERATED);
}

void Display::render(const std::vector<AGameObject*> & level) {
    // Draw the background
    SDL_SetRenderDrawColor(m_renderer, 255, 204, 0, 255);
    SDL_RenderClear(m_renderer);
    
    // Draw the gameobjects
    for (std::vector<AGameObject*>::const_iterator it = level.begin(); it != level.end(); ++it) {
        (*it)->draw(m_renderer);
    }
    
    // Present
    SDL_RenderPresent(m_renderer);
}

Display::~Display() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}