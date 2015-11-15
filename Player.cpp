#include "Player.hpp"
#include "Constants.h"
#include "SDL2_gfxPrimitives.h"

void Player::update() {
}

void Player::handleEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_a) {
            m_pos.setX(m_pos.getX() - PLAYER_SIZE);
        } else if (event.key.keysym.sym == SDLK_d) {
            m_pos.setX(m_pos.getX() + PLAYER_SIZE);
        }
    }
}

void Player::draw(SDL_Renderer* renderer) {
    boxRGBA(renderer,
            m_pos.getX(), m_pos.getY() + SCREEN_HEIGHT - PLAYER_SIZE,
            m_pos.getX() + PLAYER_SIZE, m_pos.getY() + SCREEN_HEIGHT,
            0, 242, 255, 255);
}