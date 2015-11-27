#include "Block.hpp"
#include "SDL2_gfxPrimitives.h"
#include "Constants.hpp"

Block::Block(std::pair<double, double> pos, bool movable, int color) : m_color(color), AGameObject(pos, movable, false) {}

void Block::update() {}

void Block::handleEvent(SDL_Event event) {}

void Block::draw(SDL_Renderer* renderer, int xOff) {
    boxColor(renderer,
             getPos().first + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second,
             getPos().first + Constants::PLAYER_SIZE + xOff, Constants::SCREEN_HEIGHT - getPos().second,
             m_color);
}

int Block::getColor() {
    return m_color;
}