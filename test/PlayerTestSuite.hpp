#include <cxxtest/TestSuite.h>
#include <iostream>
#include "Player.hpp"
#include "Constants.hpp"
#include <vector>
#include "SDL.h"

class PlayerTestSuite : public CxxTest::TestSuite
{
    
    std::pair<double, double> * pos1;
    Player * player1;
    AGameObject * player1generic;
    
public:
    void setUp()
    {
        pos1 = new std::pair<double, double>(0, 1 * Constants::PLAYER_SIZE);
        player1 = new Player(*pos1, true);
        player1generic = player1;
    }
    
    void tearDown()
    {
        delete pos1;
    }
 
    void test_Constructor()
    {
        TS_ASSERT(*pos1 == player1->relativePosition(0,0));
        delete player1;
    }
    
    void test_isMovable()
    {
        TS_ASSERT(player1->isMovable());
        delete player1;
    }
    
    void test_isPlayer()
    {
        TS_ASSERT(player1->isPlayer());
        delete player1;
    }
    
    void test_getPos()
    {
        TS_ASSERT_EQUALS(*pos1, player1->getPos());
        delete player1;
    }
    
    void test_handleEvent() {
        //SDL_keysym keysym1 = SDL_keysym(
        //SDL_Event event1 = SDL_Keyboard_Event(SDL_KEY_DOWN, SDL_PRESSED, keysym1);
        
    }
    
    void test_move1()
    {
        std::vector<AGameObject*> gameObjects;
        
        Block* wall1 = new Block(std::pair<double, double>(0, 0), false, Constants::WALL_COLOR);
        Block* wall2 = new Block(std::pair<double, double>(1 * Constants::PLAYER_SIZE, 0), false, Constants::WALL_COLOR);
        
        gameObjects.push_back(player1);
        gameObjects.push_back(wall1);
        gameObjects.push_back(wall2);
        
        std::pair<double, double> newPos = std::pair<double, double>(1 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE);
        
        Display * display1;
        
        display1 = new Display("Quarri", 800, 600);
        
        LevelState * state = new LevelState(gameObjects, 0, display1);
        
        player1->move(newPos);
        
        TS_ASSERT_EQUALS(newPos, player1->getPos()); //Player position actually updated
        
        AGameObject* objectFound = state->getAtPosition(newPos); //      Updated in levelstate
        TS_ASSERT(objectFound->isPlayer());
        
        delete display1;
        delete state;
    }
    
    void test_move2()
    {
        std::vector<AGameObject*> gameObjects;
        
        Block* wall1 = new Block(std::pair<double, double>(0, 0), false, Constants::WALL_COLOR);
        Block* wall2 = new Block(std::pair<double, double>(1 * Constants::PLAYER_SIZE, 0), false, Constants::WALL_COLOR);
        Block* wall3 = new Block(std::pair<double, double>(1 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE), false, Constants::WALL_COLOR);
        
        gameObjects.push_back(player1);
        gameObjects.push_back(wall1);
        gameObjects.push_back(wall2);
        gameObjects.push_back(wall3);
        
        std::pair<double, double> newPos = std::pair<double, double>(1 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE);
        
        Display * display1;
        
        display1 = new Display("Quarri", 800, 600);
        
        LevelState * state = new LevelState(gameObjects, 0, display1);
        
        player1->move(newPos); // PLayer can't move there so doesn't
        
        TS_ASSERT_EQUALS(*pos1, player1->getPos()); //Player position stays the same
        
        AGameObject* objectFound = state->getAtPosition(*pos1); // stays the same in level state
        TS_ASSERT(objectFound->isPlayer());
        
        delete display1;
        delete state;
 
    }
    
};
