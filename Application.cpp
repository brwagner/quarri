#include "Application.hpp"
#include "Display.hpp"
#include "Player.hpp"
#include "WallBlock.hpp"

void Application::start() {

  // set up the game window
  const char * name = "Quarri";// the title of the window
  int width = 800;
  int height = 600;
  Display display = Display(name, width, height);

  // the list of all the gameobjects in the level
  std::vector<AGameObject*> level;
  level.push_back(new Player());// create a new player
  level.push_back(new WallBlock());

  // the update loop
  SDL_Event event; // the event currently being handled
  bool running = true;
  while (running) {
    SDL_PumpEvents(); // clears the old events
    while (SDL_PollEvent(&event)) { //get the next event
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
