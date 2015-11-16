#include "ABlock.hpp"
#include "SDL2_gfxPrimitives.h"
#include "Constants.hpp"

void ABlock::update() {}

void ABlock::handleEvent(SDL_Event event) {}

void ABlock::draw(SDL_Renderer* renderer) {
    boxColor(renderer,
             m_pos.first, m_pos.second + Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE,
             m_pos.first + Constants::PLAYER_SIZE, m_pos.second + Constants::SCREEN_HEIGHT,
             getColor());
}