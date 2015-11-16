#ifndef LevelState_hpp
#define LevelState_hpp

#include <vector>
#include "AGameObject.hpp"
#include <utility>
#include <map>

class LevelState {
public:
    LevelState(std::vector<AGameObject*> gameObjects);
    AGameObject * getAtPosition(const std::pair<double,double> pos);
    void setAtPosition(const std::pair<double,double> pos, AGameObject * toUpdate);
    bool isAtPosition(const std::pair<double,double> pos);
private:
    std::map<std::pair<double, double>, AGameObject*> levelMap;
};

#endif
