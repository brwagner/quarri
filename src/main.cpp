#include "SDL.h"
#include "Application.hpp"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    Application().start();
    SDL_Quit();
    return 0;
}
