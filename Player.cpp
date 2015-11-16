#include "Player.hpp"
#include "SDL2_gfxPrimitives.h"
#include "Constants.hpp"

void Player::update() {
}

void Player::handleEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_a) {
            m_pos.first = (m_pos.first - Constants::PLAYER_SIZE);
        } else if (event.key.keysym.sym == SDLK_d) {
            m_pos.first = (m_pos.first + Constants::PLAYER_SIZE);
        }
    }
}

void Player::draw(SDL_Renderer* renderer) {
    boxColor(renderer,
             m_pos.first, m_pos.second + Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE,
             m_pos.first + Constants::PLAYER_SIZE, m_pos.second + Constants::SCREEN_HEIGHT,
             Constants::PLAYER_COLOR);
}