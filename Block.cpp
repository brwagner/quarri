#include "Block.hpp"
#include "SDL2_gfxPrimitives.h"
#include "Constants.hpp"

Block::Block(std::pair<double, double> pos, bool movable, int color) : m_color(color), AGameObject(pos, movable) {}

void Block::update() {}

void Block::handleEvent(SDL_Event event) {}

void Block::draw(SDL_Renderer* renderer) {
    boxColor(renderer,
             getPos().first, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second,
             getPos().first + Constants::PLAYER_SIZE, Constants::SCREEN_HEIGHT - getPos().second,
             m_color);
}