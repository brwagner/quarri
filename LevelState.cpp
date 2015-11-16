#include "LevelState.hpp"

LevelState::LevelState(std::vector<AGameObject*> gameObjects) {
    for(std::vector<AGameObject*>::const_iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
        AGameObject* current_obj = *it;
        levelMap[current_obj->getPos()] = current_obj;
    }
}

AGameObject* LevelState::getAtPosition(const std::pair<double, double> pos) {
    std::map<std::pair<double,double>,AGameObject*>::iterator it = levelMap.find(pos);
    if (it != levelMap.end()) {
        return it->second;
    }
    return NULL;
}

void LevelState::setAtPosition(const std::pair<double,double> pos, AGameObject* gameObject) {
    levelMap[pos] = gameObject;
}

bool LevelState::isAtPosition(const std::pair<double,double> pos) {
    return levelMap.find(pos) != levelMap.end();
}