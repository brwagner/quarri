#include "LevelState.hpp"
#include "Constants.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include <fstream>
#include <sstream>

typedef std::map<std::pair<double, double>, AGameObject*> level_map_t;

LevelState::LevelState(const std::string level_res_path) : m_level_res_path(level_res_path) {}

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

void LevelState::clear() {
    std::vector<AGameObject*> values;
    for(level_map_t::iterator it = m_level_map.begin(); it != m_level_map.end(); ++it) {
        values.push_back(it->second);
    }
    for (std::vector<AGameObject*>::iterator it = values.begin(); it != values.end(); ++it) {
        m_level_map.erase(m_level_map.find((*it)->getPos()));
    }
}

void LevelState::loadLevel(int level_index) {
    clear();
    std::string level_to_load = m_level_res_path;
    std::stringstream out;
    out << level_index;
    level_to_load += out.str() + ".quar";
    std::ifstream level_in(level_to_load);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(level_in, line)) {
        lines.push_back(line);
    }
    double y = 0;
    double x = 0;
    for(std::vector<std::string>::reverse_iterator rit = lines.rbegin(); rit != lines.rend(); ++rit, x = 0, y += Constants::PLAYER_SIZE)
    {
        for(std::string::iterator it = rit->begin(); it != rit->end(); ++it, x += Constants::PLAYER_SIZE) {
            std::pair<double, double> pos = std::make_pair(x, y);
            AGameObject* current_obj;
            if (*it == 'X') {
                current_obj = new Block(pos, false, Constants::WALL_COLOR);
            } else if (*it == 'M') {
                current_obj = new Block(pos, true, Constants::MOVABLE_COLOR);
            } else if (*it == 'P') {
                current_obj = new Player(pos, false);
            } else {
                current_obj = NULL;
            }
            if (current_obj) {
                current_obj->setLevelState(this);
                m_level_map[current_obj->getPos()] = current_obj;
            }
        }
    }
}