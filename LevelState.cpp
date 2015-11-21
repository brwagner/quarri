#include "LevelState.hpp"
#include "Constants.hpp"
#include "Block.hpp"
#include "Player.hpp"
#include <fstream>
#include <sstream>

typedef std::map<std::pair<double, double>, AGameObject*> level_map_t;
typedef std::pair<std::pair<double,double>, AGameObject*> level_map_kvp_t;

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
    std::vector<AGameObject*> values = getValueList();
    display->render(&values);
}

void LevelState::handleEvent(SDL_Event event) {
    std::vector<level_map_kvp_t> kvps = getKeyValueList();
    for (std::vector<level_map_kvp_t>::const_iterator it = kvps.begin(); it != kvps.end(); ++it) {
        it->second->handleEvent(event);
    }
}

void LevelState::loadLevel(int level_index) {
    // clear the map of existing gameobjects
    m_level_map.clear();
    // get the path of the level to load
    std::string level_to_load = m_level_res_path;
    std::stringstream out;
    out << level_index;
    level_to_load += out.str() + ".quar";
    // create the file stream
    std::ifstream level_in(level_to_load);
    
    // read lines into a vector
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(level_in, line)) {
        lines.push_back(line);
    }
    
    // build up the level by iterating in reverse order through the rows and forward order through the columns
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

std::vector<level_map_kvp_t> LevelState::getKeyValueList() {
    std::vector<level_map_kvp_t> dest;
    for(level_map_t::const_iterator it = m_level_map.begin(); it != m_level_map.end(); ++it) {
        dest.push_back(*it);
    }
    return dest;
}

std::vector<AGameObject*> LevelState::getValueList() {
    std::vector<AGameObject*> values;
    for(level_map_t::iterator it = m_level_map.begin(); it != m_level_map.end(); ++it) {
        values.push_back(it->second);
    }
    return values;
}