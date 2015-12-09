#include "Block.hpp"
#include "SDL2_gfxPrimitives.h"
#include "Constants.hpp"

Block::Block(std::pair<double, double> pos, bool movable, int color) : m_color(color), AGameObject(pos, movable, false) {}

void Block::update() {}

void Block::handleEvent(SDL_Event event) {}

void Block::draw(SDL_Renderer* renderer, int xOff) {
    if (isMovable()) {
        //box background
        boxColor(renderer,
            getPos().first + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second,
            getPos().first + Constants::PLAYER_SIZE + xOff, Constants::SCREEN_HEIGHT - getPos().second,
            m_color);

        // line 1 (far left)
        lineColor(renderer,
            getPos().first + Constants::MOVE_BOX_SPACING + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::MOVE_BOX_SPACING - getPos().second,
            getPos().first + Constants::MOVE_BOX_SPACING + xOff, Constants::SCREEN_HEIGHT - Constants::MOVE_BOX_SPACING - getPos().second,
            Constants::LINE_COLOR);

        // line 2
        lineColor(renderer,
            getPos().first + (2 * Constants::MOVE_BOX_SPACING) + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::MOVE_BOX_SPACING - getPos().second,
            getPos().first + (2 * Constants::MOVE_BOX_SPACING) + xOff, Constants::SCREEN_HEIGHT - Constants::MOVE_BOX_SPACING - getPos().second,
            Constants::LINE_COLOR);

        // line 3
        lineColor(renderer,
            getPos().first + (3 * Constants::MOVE_BOX_SPACING) + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::MOVE_BOX_SPACING - getPos().second,
            getPos().first + (3 * Constants::MOVE_BOX_SPACING) + xOff, Constants::SCREEN_HEIGHT - Constants::MOVE_BOX_SPACING - getPos().second,
            Constants::LINE_COLOR);

        // line 4
        lineColor(renderer,
            getPos().first + (4 * Constants::MOVE_BOX_SPACING) + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::MOVE_BOX_SPACING - getPos().second,
            getPos().first + (4 * Constants::MOVE_BOX_SPACING) + xOff, Constants::SCREEN_HEIGHT - Constants::MOVE_BOX_SPACING - getPos().second,
            Constants::LINE_COLOR);


        // top outline
        boxColor(renderer,
            getPos().first + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second,
            getPos().first + Constants::PLAYER_SIZE + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::MOVE_BOX_SPACING - getPos().second,
            Constants::BOX_TOP_BOTTOM_COLOR);

        //bottom outline
        boxColor(renderer,
            getPos().first + xOff, Constants::SCREEN_HEIGHT - Constants::MOVE_BOX_SPACING - getPos().second,
            getPos().first + Constants::PLAYER_SIZE + xOff, Constants::SCREEN_HEIGHT - getPos().second,
            Constants::BOX_TOP_BOTTOM_COLOR);
    }
    else {
        // background
        boxColor(renderer,
            getPos().first + xOff, Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - getPos().second,
            getPos().first + Constants::PLAYER_SIZE + xOff, Constants::SCREEN_HEIGHT - getPos().second,
            m_color);

        // brick 1 (upper left)
        boxColor(renderer,
            getPos().first + xOff, 
            Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::BETWEEN_BRICK_SPACE - getPos().second,
            getPos().first + Constants::BRICK_FULL_WIDTH + xOff, 
            Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::BETWEEN_BRICK_SPACE + Constants::BRICK_HEIGHT - getPos().second,
            Constants::BRICK_COLOR);

        // brick 2 (upper right)
        boxColor(renderer,
            getPos().first + Constants::BRICK_FULL_WIDTH + Constants::BETWEEN_BRICK_WIDTH + xOff, 
            Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE - Constants::BETWEEN_BRICK_SPACE - getPos().second,
            getPos().first + Constants::PLAYER_SIZE + xOff, 
            Constants::SCREEN_HEIGHT - Constants::PLAYER_SIZE + Constants::BETWEEN_BRICK_SPACE + Constants::BRICK_HEIGHT - getPos().second,
            Constants::BRICK_COLOR);

        // brick 3 (mid left)
        boxColor(renderer,
            getPos().first + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - Constants::BETWEEN_BRICK_SPACE_MIDDLE - (2 * Constants::BRICK_HEIGHT) - getPos().second,
            getPos().first + Constants::BRICK_FULL_WIDTH + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - Constants::BETWEEN_BRICK_SPACE_MIDDLE -  Constants::BRICK_HEIGHT - getPos().second,
            Constants::BRICK_COLOR);

        // brick 4 (mid mid)
        boxColor(renderer,
            getPos().first + Constants::BRICK_HALF_WIDTH + Constants::BETWEEN_BRICK_WIDTH + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - Constants::BETWEEN_BRICK_SPACE_MIDDLE - (2 * Constants::BRICK_HEIGHT) - getPos().second,
            getPos().first + Constants::BRICK_HALF_WIDTH + Constants::BETWEEN_BRICK_WIDTH + Constants::BRICK_FULL_WIDTH + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - Constants::BETWEEN_BRICK_SPACE_MIDDLE - Constants::BRICK_HEIGHT - getPos().second,
            Constants::BRICK_COLOR);

        // brick 5 (mid right)
        boxColor(renderer,
            getPos().first + Constants::PLAYER_SIZE - Constants::BRICK_HALF_WIDTH + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - Constants::BETWEEN_BRICK_SPACE_MIDDLE - (2 * Constants::BRICK_HEIGHT) - getPos().second,
            getPos().first + Constants::PLAYER_SIZE + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - Constants::BETWEEN_BRICK_SPACE_MIDDLE - Constants::BRICK_HEIGHT - getPos().second,
            Constants::BRICK_COLOR);

        // brick 6 (bottom left)
        boxColor(renderer,
            getPos().first + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - Constants::BRICK_HEIGHT - getPos().second,
            getPos().first + Constants::BRICK_FULL_WIDTH + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - getPos().second,
            Constants::BRICK_COLOR);

        // brick 7 (bottom right)
        boxColor(renderer,
            getPos().first + Constants::BRICK_FULL_WIDTH + Constants::BETWEEN_BRICK_WIDTH + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - Constants::BRICK_HEIGHT - getPos().second,
            getPos().first + Constants::PLAYER_SIZE + xOff, 
            Constants::SCREEN_HEIGHT - Constants::BETWEEN_BRICK_SPACE - getPos().second,
            Constants::BRICK_COLOR);
    }
}

int Block::getColor() {
    return m_color;
}