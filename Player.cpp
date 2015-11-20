#include "Player.hpp"
#include "SDL2_gfxPrimitives.h"
#include "Constants.hpp"

Player::Player(std::pair<double, double> pos, bool movable) : m_held(NULL), AGameObject(pos, movable) {}

void Player::update() {}

void Player::handleEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_a) {
            move(left());
        } else if (event.key.keysym.sym == SDLK_d) {
            move(right());
        } else if (event.key.keysym.sym == SDLK_s) {
            if (m_held) {
                if (m_held->move(left())) {
                    m_held = NULL;
                }
            }
            else if (m_level_state->isAtPosition(left())) {
                AGameObject* go = m_level_state->getAtPosition(left());
                if (go->isMovable()) {
                    m_held = go;
                    m_held->move(up());
                }
            }
        }
    }
}

bool Player::move(std::pair<double, double> pos) {
    if (m_held) {
        std::pair<double, double> pos_up = std::pair<double, double>(pos);
        pos_up.second += Constants::PLAYER_SIZE;
        return m_held->move(pos_up) && AGameObject::move(pos);
    } else {
        return AGameObject::move(pos);
    }
}

void Player::draw(SDL_Renderer* renderer) {
    boxColor(renderer,
             getPos().first, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second,
             getPos().first + Constants::PLAYER_SIZE, Constants::SCREEN_HEIGHT - getPos().second,
             Constants::PLAYER_COLOR);
}