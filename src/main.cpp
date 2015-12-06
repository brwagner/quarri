#include "SDL.h"
#include "SDL_mixer.h"
#include "Application.hpp"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    Application().start();
    SDL_Quit();
    return 0;
}
