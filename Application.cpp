#include "Application.hpp"
#include "Display.hpp"
#include "Player.hpp"
#include "LevelState.hpp"
#include "Constants.hpp"

void Application::start() {

    // set up the game window
    const char * name = "Quarri";// the title of the window
    int width = 800;
    int height = 600;
    Display display = Display(name, width, height);

    LevelState levelState("res/level/", 1);
    
    // the update loop
    SDL_Event event; // the event currently being handled
    bool running = true;
    while (running) {
        SDL_PumpEvents(); // clears the old events
        while (SDL_PollEvent(&event)) { //get the next event
            if (event.type == SDL_QUIT) {
                  running = false;
            }
            levelState.handleEvent(event);
        }
        levelState.update();
        levelState.renderTo(&display);
    }
}