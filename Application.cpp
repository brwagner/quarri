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

    // the list of all the gameobjects in the level
    std::vector<AGameObject*> level;
    level.push_back(new Player(std::make_pair(100.0,0.0), true));// create a new player
    level.push_back(new Block(std::make_pair(0.0,0.0), true, Constants::WALL_COLOR));
    LevelState levelState(&level);

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