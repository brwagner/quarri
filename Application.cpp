#include "Application.hpp"

#include "Display.hpp"
#include "Player.hpp"

void Application::start() {
    const char * name = "Quarri";
    int width = 800;
    int height = 600;
    Display display = Display(name, width, height);
    
    std::vector<AGameObject*> level;
    level.push_back(new Player());
        
    SDL_Event event;
    bool running = true;
    while (running) {
        SDL_PumpEvents();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            handleGameEvents(event, level);
            update(level);
        }
        display.render(level);
    }
}

void Application::handleGameEvents(SDL_Event event, const std::vector<AGameObject*> & level) {
    for(std::vector<AGameObject*>::const_iterator it = level.begin(); it != level.end(); ++it) {
        (*it)->handleEvent(event);
    }
}

void Application::update(const std::vector<AGameObject*> & level) {
    for(std::vector<AGameObject*>::const_iterator it = level.begin(); it != level.end(); ++it) {
        (*it)->update();
    }
}