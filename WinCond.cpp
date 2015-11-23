#include "WinCond.hpp"
#include "Constants.hpp"
#include "SDL.h"

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