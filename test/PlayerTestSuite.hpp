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
    Display * display1;
    LevelState * state;
    
public:
    void setUp()
    {
        pos1 = new std::pair<double, double>(0, 1 * Constants::PLAYER_SIZE);
        player1 = new Player(*pos1, true);
        player1generic = player1;
        
        std::vector<AGameObject*> gameObjects;
        
        Block* wall1 = new Block(std::pair<double, double>(0, 0), false, Constants::WALL_COLOR);
        Block* wall2 = new Block(std::pair<double, double>(1 * Constants::PLAYER_SIZE, 0), false, Constants::WALL_COLOR);
        Block* wall3 = new Block(std::pair<double, double>(1 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE), false, Constants::WALL_COLOR);
        Block* wall4 = new Block(std::pair<double, double>(1 * Constants::PLAYER_SIZE, 2 * Constants::PLAYER_SIZE), false, Constants::WALL_COLOR);
        Block* wall5 = new Block(std::pair<double, double>(-2 * Constants::PLAYER_SIZE, 0), false, Constants::WALL_COLOR);
        Block* wall6 = new Block(std::pair<double, double>(-2 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE), true, Constants::WALL_COLOR);
        Block* wall7 = new Block(std::pair<double, double>(-1 * Constants::PLAYER_SIZE, 0), false, Constants::WALL_COLOR);
        
        // Makes a level where theres a movable block to spaces to the left of the player, and a two layer high wall directly to the right
        
        gameObjects.push_back(player1);
        gameObjects.push_back(wall1);
        gameObjects.push_back(wall2);
        gameObjects.push_back(wall3);
        gameObjects.push_back(wall4);
        gameObjects.push_back(wall5);
        gameObjects.push_back(wall6);
        gameObjects.push_back(wall7);
        
        display1 = new Display("Quarri", 800, 600);
        
        state = new LevelState(gameObjects, 0, display1);
        
    }
    
    void tearDown()
    {
        delete pos1;
        
        delete display1;
        delete state;
    }
 
    void test_Constructor()
    {
        TS_ASSERT(*pos1 == player1->relativePosition(0,0));
    }
    
    void test_isMovable()
    {
        TS_ASSERT(player1->isMovable());
    }
    
    void test_isPlayer()
    {
        TS_ASSERT(player1->isPlayer());
    }
    
    void test_getPos()
    {
        TS_ASSERT_EQUALS(*pos1, player1->getPos());
    }
    
    void test_handleEvent1() {
        //SDL_keysym keysym1 = SDL_keysym(
        SDL_Event event1;
        event1.type = SDL_KEYDOWN;
        event1.key.keysym.sym = SDLK_a;
        
        std::pair<double, double> newPos = std::pair<double, double>(-1 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE);
        
        player1->handleEvent(event1); // Starts facing left so just moves left
        TS_ASSERT_EQUALS(newPos, player1->getPos()); //Player position updated
    }
    
    void test_handleEvent2() {
        //SDL_keysym keysym1 = SDL_keysym(
        SDL_Event event1;
        event1.type = SDL_KEYDOWN;
        event1.key.keysym.sym = SDLK_s;
        
        SDL_Event event2;
        event2.type = SDL_KEYDOWN;
        event2.key.keysym.sym = SDLK_a;
        
        SDL_Event event3;
        event3.type = SDL_KEYDOWN;
        event3.key.keysym.sym = SDLK_d;
        
        std::pair<double, double> newPos = std::pair<double, double>(0, 1 * Constants::PLAYER_SIZE);
        
        player1->handleEvent(event2); // Moves left
        player1->handleEvent(event1); // Picks up the block
        player1->handleEvent(event3); // Moves right with the block
        player1->handleEvent(event3);
        TS_ASSERT_EQUALS(newPos, player1->getPos()); //Player position actually updated
        
        std::pair<double, double> blockPos = std::pair<double, double>(0, 2 * Constants::PLAYER_SIZE);
        
        AGameObject* objectFound =  state->getAtPosition(blockPos); // Block was picked up and moved with player
        TS_ASSERT(!objectFound->isPlayer());
        
    }
    
    void test_move1()
    {
        std::pair<double, double> newPos = std::pair<double, double>(-1 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE);
        
        player1->move(newPos);
        
        TS_ASSERT_EQUALS(newPos, player1->getPos()); //Player position actually updated
        
        AGameObject* objectFound = state->getAtPosition(newPos); //      Updated in levelstate
        TS_ASSERT(objectFound->isPlayer());

    }
    
    void test_move2()
    {

        std::pair<double, double> newPos = std::pair<double, double>(1 * Constants::PLAYER_SIZE, 1 * Constants::PLAYER_SIZE);
        std::pair<double, double> origPos = std::pair<double, double>(0, 1 * Constants::PLAYER_SIZE);
        
        player1->move(newPos); // PLayer can't move there so doesn't
        
        TS_ASSERT_EQUALS(origPos, player1->getPos()); //Player position stays the same
        
        AGameObject* objectFound = state->getAtPosition(origPos); // stays the same in level state
        TS_ASSERT(objectFound->isPlayer());
    }
    
};
