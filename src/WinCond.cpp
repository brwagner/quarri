#include "WinCond.hpp"
#include "Constants.hpp"
#include "SDL2_gfxPrimitives.h"

WinCond::WinCond(std::pair<double, double> pos) : Block(pos, false, Constants::WIN_COND_COLOR) {}

void WinCond::update() {
    for (double x = left().first; x <= right().first; x += Constants::PLAYER_SIZE) {
        for (double y = up().second; y >= down().second; y -= Constants::PLAYER_SIZE) {
            std::pair<double, double> pos = std::make_pair<double, double>(x, y);
            if (pos != getPos()) {
                if (m_level_state->isAtPosition(pos)) {
                    AGameObject* obj = m_level_state->getAtPosition(pos);
                    if (obj->isPlayer()) {
                        m_level_state->registerWin();
                    }
                }
            }
        }
    }
}

void WinCond::draw(SDL_Renderer* renderer, int xOff) {
  // flag pole
  boxColor(renderer, 
          getPos().first + Constants::FLAG_POLE_LEFT, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second, 
          getPos().first + Constants::FLAG_POLE_RIGHT, Constants::SCREEN_HEIGHT - getPos().second,
          Constants::WIN_COND_POLE_COLOR);
  
  // triangle flag
  filledTrigonColor(renderer,
                   getPos().first + Constants::FLAG_POLE_RIGHT, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second, 
                   getPos().first + Constants::FLAG_POLE_RIGHT, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second + 10, 
                   getPos().first + Constants::PLAYER_SIZE, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second + 5, 
                   Constants::WIN_COND_COLOR);
}