#include "WallBlock.hpp"
#include "Constants.hpp"

bool WallBlock::isMovable() {
    return false;
}

int WallBlock::getColor() {
    return Constants::WALL_COLOR;
}