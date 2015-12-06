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
    double x = getPos().first + xOff;
    double y = getPos().second;
    if (m_dir == RIGHT && !m_held) {
    //Quarri facing right
    // monitor front
    boxColor(renderer,
            x + Constants::PLAYER_BACK, Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT - y,
            x + Constants::PLAYER_SIZE - Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - y,
            Constants::MONITOR_COLOR);
    
    // monitor shading
    boxColor(renderer,
            x + Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT - y,
            x + Constants::BOX_SPACE + Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - y,
            Constants::MONITOR_SHADING_COLOR);
    
    // screen
    boxColor(renderer,
            x + Constants::BOX_SPACE + Constants::PLAYER_BACK,
            Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
            x + (6.9 * Constants::BOX_SPACE) - Constants::SHADE_WIDTH + Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
            Constants::SCREEN_COLOR);
    
    // left tire
    filledEllipseColor(renderer,
                      x + Constants::BOX_SPACE + Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::TIRE_COLOR);
    
    // right tire
    filledEllipseColor(renderer,
                      x + (7 * Constants::BOX_SPACE), Constants::SCREEN_HEIGHT - Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::TIRE_COLOR);
    
    // left eye
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - 4 * Constants::BOX_SPACE - Constants::EYE_WIDTH - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT + 2 * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 4 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT * 1.25 + 3 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // right eye
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::EYE_WIDTH - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT + 2 * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT * 1.25 + 3 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // mouth
    boxColor(renderer,
            x + 2 * Constants::BOX_SPACE + Constants::PLAYER_BACK - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - 2 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // left arm
    lineColor(renderer,
             x + (Constants::BOX_SPACE / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
             x + Constants::BOX_SPACE + (Constants::SHADE_WIDTH / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
             Constants::TIRE_COLOR);
    
    // right arm
    lineColor(renderer,
             x + Constants::PLAYER_SIZE + (Constants::BOX_SPACE / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
             x + Constants::PLAYER_SIZE, Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
             Constants::TIRE_COLOR);
    
    // left hand
    filledEllipseColor(renderer,
                      x + (Constants::BOX_SPACE / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::MONITOR_COLOR);
    
    // right hand
    filledEllipseColor(renderer,
                      x + Constants::PLAYER_SIZE + (Constants::BOX_SPACE / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::MONITOR_COLOR);
  }
  else if (m_dir == RIGHT && m_held) {
    // facing right arms up
    // monitor front
    boxColor(renderer,
            x + Constants::PLAYER_BACK, Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT - y,
            x + Constants::PLAYER_SIZE - Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - y,
            Constants::MONITOR_COLOR);
    
    // monitor shading
    boxColor(renderer,
            x + Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT - y,
            x + Constants::BOX_SPACE + Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - y,
            Constants::MONITOR_SHADING_COLOR);
    
    // screen
    boxColor(renderer,
            x + Constants::BOX_SPACE + Constants::PLAYER_BACK,
            Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
            x + (6.9 * Constants::BOX_SPACE) - Constants::SHADE_WIDTH + Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
            Constants::SCREEN_COLOR);
    
    // left tire
    filledEllipseColor(renderer,
                      x + Constants::BOX_SPACE + Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::TIRE_COLOR);
    
    // right tire
    filledEllipseColor(renderer,
                      x + (7 * Constants::BOX_SPACE), Constants::SCREEN_HEIGHT - Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::TIRE_COLOR);
    
    // left eye
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - 4 * Constants::BOX_SPACE - Constants::EYE_WIDTH - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT + 2 * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 4 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT * 1.25 + 3 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // right eye
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::EYE_WIDTH - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT + 2 * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT * 1.25 + 3 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // mouth
    boxColor(renderer,
            x + 2 * Constants::BOX_SPACE + Constants::PLAYER_BACK - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - 2 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // left arm
    lineColor(renderer,
             x + Constants::BOX_SPACE + (Constants::SHADE_WIDTH / 2), Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::TIRE_RADIUS - y,
             x + Constants::BOX_SPACE + (Constants::SHADE_WIDTH / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
             Constants::TIRE_COLOR);
    
    // right arm
    lineColor(renderer,
             x + Constants::PLAYER_SIZE, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::TIRE_RADIUS - y,
             x + Constants::PLAYER_SIZE, Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
             Constants::TIRE_COLOR);
    
    // left hand
    filledEllipseColor(renderer,
                      x + Constants::BOX_SPACE + (Constants::SHADE_WIDTH / 2), Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::MONITOR_COLOR);
    
    // right hand
    filledEllipseColor(renderer,
                      x + Constants::PLAYER_SIZE, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::MONITOR_COLOR);
  }
  else if (m_dir == LEFT && !m_held) {
    // facing left
    // monitor front
    boxColor(renderer,
            x + Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT - y,
            x + Constants::PLAYER_SIZE - Constants::BOX_SPACE - Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - y,
            Constants::MONITOR_COLOR);
    
    // monitor shading
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - Constants::BOX_SPACE - Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT - y,
            x + Constants::PLAYER_SIZE - Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - y,
            Constants::MONITOR_SHADING_COLOR);
    
    // screen
    boxColor(renderer,
            x + Constants::BOX_SPACE + Constants::PLAYER_BACK - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
            x + (6.9 * Constants::BOX_SPACE) - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
            Constants::SCREEN_COLOR);
    
    // left tire
    filledEllipseColor(renderer,
                      x + Constants::BOX_SPACE + Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::TIRE_COLOR);
    
    // right tire
    filledEllipseColor(renderer,
                      x + (7 * Constants::BOX_SPACE), Constants::SCREEN_HEIGHT - Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::TIRE_COLOR);
    
    // left eye
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - 4 * Constants::BOX_SPACE - Constants::EYE_WIDTH - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT + 2 * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 4 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT * 1.25 + 3 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // right eye
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::EYE_WIDTH - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT + 2 * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT * 1.25 + 3 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // mouth
    boxColor(renderer,
            x + 2 * Constants::BOX_SPACE + Constants::PLAYER_BACK - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - 2 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // left arm
    lineColor(renderer,
             x + (Constants::BOX_SPACE / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
             x + Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
             Constants::TIRE_COLOR);
    
    // right arm
    lineColor(renderer,
             x + Constants::PLAYER_SIZE + (Constants::BOX_SPACE / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
             x + Constants::PLAYER_SIZE - (Constants::SHADE_WIDTH / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
             Constants::TIRE_COLOR);
    
    // left hand
    filledEllipseColor(renderer,
                      x + (Constants::BOX_SPACE / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::MONITOR_COLOR);
    
    // right hand
    filledEllipseColor(renderer,
                      x + Constants::PLAYER_SIZE + (Constants::BOX_SPACE / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::MONITOR_COLOR);
  }
  else if (m_dir == LEFT && m_held) {
    // facing left arms up
    // monitor front
    boxColor(renderer,
            x + Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT - y,
            x + Constants::PLAYER_SIZE - Constants::BOX_SPACE - Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - y,
            Constants::MONITOR_COLOR);
    
    // monitor shading
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - Constants::BOX_SPACE - Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT - y,
            x + Constants::PLAYER_SIZE - Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - y,
            Constants::MONITOR_SHADING_COLOR);
    
    // screen
    boxColor(renderer,
            x + Constants::BOX_SPACE + Constants::PLAYER_BACK - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
            x + (6.9 * Constants::BOX_SPACE) - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::SCREEN_BOTTOM - y,
            Constants::SCREEN_COLOR);
    
    // left tire
    filledEllipseColor(renderer,
                      x + Constants::BOX_SPACE + Constants::SHADE_WIDTH, Constants::SCREEN_HEIGHT - Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::TIRE_COLOR);
    
    // right tire
    filledEllipseColor(renderer,
                      x + (7 * Constants::BOX_SPACE), Constants::SCREEN_HEIGHT - Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::TIRE_COLOR);
    
    // left eye
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - 4 * Constants::BOX_SPACE - Constants::EYE_WIDTH - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT + 2 * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 4 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT * 1.25 + 3 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // right eye
    boxColor(renderer,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::EYE_WIDTH - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT + 2 * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_HEIGHT * 1.25 + 3 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // mouth
    boxColor(renderer,
            x + 2 * Constants::BOX_SPACE + Constants::PLAYER_BACK - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM * Constants::BOX_SPACE - y,
            x + Constants::PLAYER_SIZE - 2 * Constants::BOX_SPACE - Constants::SHADE_WIDTH,
            Constants::SCREEN_HEIGHT - Constants::PLAYER_BOTTOM - 2 * Constants::BOX_SPACE - y,
            Constants::SCREEN_FACE_COLOR);
    
    // left arm
    lineColor(renderer,
             x + Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::TIRE_RADIUS - y,
             x + Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
             Constants::TIRE_COLOR);
    
    // right arm
    lineColor(renderer,
             x + Constants::PLAYER_SIZE - (Constants::SHADE_WIDTH / 2), Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::TIRE_RADIUS - y,
             x + Constants::PLAYER_SIZE - (Constants::SHADE_WIDTH / 2), Constants::SCREEN_HEIGHT - Constants::SCREEN_TOP - y,
             Constants::TIRE_COLOR);
    
    // left hand
    filledEllipseColor(renderer,
                      x + Constants::BOX_SPACE, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::MONITOR_COLOR);
    
    // right hand
    filledEllipseColor(renderer,
                      x + Constants::PLAYER_SIZE - (Constants::SHADE_WIDTH / 2), Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::TIRE_RADIUS - y,
                      Constants::TIRE_RADIUS, Constants::TIRE_RADIUS,
                      Constants::MONITOR_COLOR);
  }
}
