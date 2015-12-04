#include "Player.hpp"
#include "SDL2_gfxPrimitives.h"
#include "Constants.hpp"

#define LEFT -1
#define RIGHT 1

Player::Player(std::pair<double, double> pos, bool movable) : m_held(NULL), m_dir(LEFT), AGameObject(pos, movable, true) {
    m_boop_sound = Mix_LoadWAV("res/sounds/boop.wav");
    m_woosh_sound = Mix_LoadWAV("res/sounds/woosh.wav");
}

Player::~Player() {
    Mix_FreeChunk(m_boop_sound);
    Mix_FreeChunk(m_woosh_sound);
}

void Player::update() {}

void Player::handleEvent(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_LEFT) {
            m_level_state->moveCamera(Constants::CAMERA_MOVE_AMOUNT);
        }
        else if (event.key.keysym.sym == SDLK_RIGHT) {
            m_level_state->moveCamera(-Constants::CAMERA_MOVE_AMOUNT);
        }
        else if (isMoving(event)) {
            // check if we're moving the direction we're facing
            if (isMovingTowardsDir(event)) {
                // Try to move up a level if possible if not try forward
                if (move(forwardUpPos()) || move(forwardPos())) {
                    Mix_PlayChannel(-1, m_boop_sound, 0);
                }
            } else {
                m_dir *= -1; // flip the player
                Mix_PlayChannel(-1, m_woosh_sound, 0);
            }
        } else if (event.key.keysym.sym == SDLK_s) {
            if (m_held) {
                if (m_held->move(forwardPos())) {
                    m_held = NULL;
                }
            } else if (isPickupValid()) {
                AGameObject* go = m_level_state->getAtPosition(forwardPos());
                if (go->isMovable()) {
                    m_held = go;
                    m_held->move(up());
                }
            }
        }
    }
}

std::pair<double, double> Player::forwardPos() {
    return relativePosition(m_dir, 0);
}

std::pair<double, double> Player::forwardUpPos() {
    return relativePosition(m_dir, 1);
}

bool Player::isMoving(SDL_Event event) {
    return event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d;
}

bool Player::isMovingTowardsDir(SDL_Event event) {
    return (event.key.keysym.sym == SDLK_a && m_dir == LEFT) || (event.key.keysym.sym == SDLK_d && m_dir == RIGHT);
}

bool Player::isPickupValid() {
    return m_level_state->isAtPosition(forwardPos())
        && !m_level_state->isAtPosition(relativePosition(m_dir*1,1))
        && !m_level_state->isAtPosition(up());
}

bool Player::move(std::pair<double, double> pos) {
    if (m_held) {
        std::pair<double, double> pos_up = std::pair<double, double>(pos);
        pos_up.second += Constants::PLAYER_SIZE;
        if (!m_level_state->isAtPosition(pos) && !m_level_state->isAtPosition(pos_up)) {
            AGameObject::move(pos) && m_held->move(pos_up);
            return true;
        }
        return false;
    } else {
        return AGameObject::move(pos);
    }
}

void Player::draw(SDL_Renderer* renderer, int xOff) {
    boxColor(renderer,
             getPos().first + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second,
             getPos().first + Constants::PLAYER_SIZE + xOff, Constants::SCREEN_HEIGHT - getPos().second,
             Constants::PLAYER_COLOR);
}
