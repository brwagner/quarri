#ifndef Application_hpp
#define Application_hpp

#include "SDL.h"
#include <vector>
#include "AGameObject.hpp"

class Application {
public:
    void start();
private:
    void handleGameEvents(SDL_Event event, const std::vector<AGameObject*> & level);
    void update(const std::vector<AGameObject*> & level);
};

#endif
