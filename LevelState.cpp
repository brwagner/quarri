#include "LevelState.hpp"

typedef std::map<std::pair<double, double>, AGameObject*> level_map_t;

LevelState::LevelState(std::vector<AGameObject*>* gameObjects) {
    for(std::vector<AGameObject*>::const_iterator it = gameObjects->begin(); it != gameObjects->end(); ++it) {
        AGameObject* current_obj = *it;
        current_obj->setLevelState(this);
        m_level_map[current_obj->getPos()] = current_obj;
    }
}

AGameObject* LevelState::getAtPosition(const std::pair<double, double> pos) {
    level_map_t::iterator it = m_level_map.find(pos);
    if (it != m_level_map.end()) {
        return it->second;
    }
    return NULL;
}

bool LevelState::move(const std::pair<double,double> from, const std::pair<double,double> to) {
    level_map_t::iterator fromIt = m_level_map.find(from);
    level_map_t::iterator toIt = m_level_map.find(to);
    bool success = fromIt != m_level_map.end() && toIt == m_level_map.end();
    if (success) {
        m_level_map[to] = m_level_map[from];
        m_level_map.erase(fromIt);
    }
    return success;
}

bool LevelState::isAtPosition(const std::pair<double,double> pos) {
    return m_level_map.find(pos) != m_level_map.end();
}

void LevelState::update() {
    for (level_map_t::iterator it = m_level_map.begin(); it != m_level_map.end(); it++) {
        it->second->update();
    }
}

void LevelState::renderTo(Display* display) {
    std::vector<AGameObject*> values;
    for(level_map_t::iterator it = m_level_map.begin(); it != m_level_map.end(); ++it) {
        values.push_back(it->second);
    }
    display->render(&values);
}

void LevelState::handleEvent(SDL_Event event) {
    std::vector<AGameObject*> values;
    for(level_map_t::iterator it = m_level_map.begin(); it != m_level_map.end(); ++it) {
        values.push_back(it->second);
    }
    for (std::vector<AGameObject*>::const_iterator it = values.begin(); it != values.end(); ++it) {
        (*it)->handleEvent(event);
    }
}