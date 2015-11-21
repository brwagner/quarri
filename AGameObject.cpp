#include "AGameObject.hpp"
#include "Constants.hpp"

AGameObject::AGameObject(std::pair<double, double> pos, bool movable) : m_pos(pos), m_movable(movable) {}

const std::pair<double, double> AGameObject::getPos() const { return m_pos; }

bool AGameObject::move(std::pair<double, double> pos) {
    if (m_level_state->move(m_pos, pos)) {
        m_pos = pos;
        move(down());
        return true;
    }
    return false;
}

void AGameObject::setLevelState(LevelState * level_state) { m_level_state = level_state; }

const bool AGameObject::isMovable() const { return m_movable; }

std::pair<double, double> AGameObject::relativePosition(int x, int y) {
    std::pair<double, double> pos = getPos();
    pos.first += Constants::PLAYER_SIZE * x;
    pos.second += Constants::PLAYER_SIZE * y;
    return pos;
}

std::pair<double, double> AGameObject::up() {
    return relativePosition(0,1);
}

std::pair<double, double> AGameObject::down() {
    return relativePosition(0,-1);
}

std::pair<double, double> AGameObject::left() {
    return relativePosition(-1,0);
}

std::pair<double, double> AGameObject::right() {
    return relativePosition(1,0);
}